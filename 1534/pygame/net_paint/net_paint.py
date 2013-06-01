#!/usr/bin/env python3

import sys
import socket

from random import randrange

import pygame
from pygame.locals import *
pygame.init()


FPS = 50
WHITE = (255, 255, 255)            


def init_display():
    global DISPLAYSURF, MY_COLOR, Clock

    DISPLAYSURF = pygame.display.set_mode((400, 300), 0, 32)
    DISPLAYSURF.fill(WHITE)
    pygame.display.set_caption('Net paint ' + ' '.join(sys.argv))

    MY_COLOR = [randrange(256) for i in range(3)]

    Clock = pygame.time.Clock()


def print_help_and_exit():
    print('''Usage:
    net_paint.py client SERVER_IPv4_ADDR PORT
    net_paint.py server PORT
    ''')
    sys.exit(1)


def init_network():
    global my_socket, my_type, client_socket
        
    my_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)   
    
    if len(sys.argv) < 2:
        print_help_and_exit()
        
    my_type = sys.argv[1]
    if sys.argv[1] == 'client':
        if len(sys.argv) != 4:
            print_help_and_exit()
        server_addr, port = sys.argv[2:]
        my_socket.connect((server_addr, int(port)))
    elif sys.argv[1] == 'server':
        if len(sys.argv) != 3:
            print_help_and_exit()
        port = sys.argv[2]
        my_socket.bind(('127.0.0.1', int(port)))
        my_socket.listen(1)
        client_socket, client_addr = my_socket.accept()
        client_socket.setblocking(False)
    else:
        print_help_and_exit()
    
    my_socket.setblocking(False)


def send_point_to_server(pos):
    if my_type == 'client':
        my_list = list(pos) + MY_COLOR
        my_socket.send(bytes(' '.join([str(i) for i in my_list]) + '\n', 'utf-8'))
    else:
        recv_point_on_server(pos, MY_COLOR)
        
        
def recv_point_on_server(pos, color):
    draw_point(pos, color)
    my_list = list(pos) + list(color)
    client_socket.send(bytes(' '.join([str(i) for i in my_list]) + '\n', 'utf-8'))
    
    
def draw_point(pos, color):
    pygame.draw.circle(DISPLAYSURF, color, pos, 3)


def watch_socket():
    try:
        if my_type == 'client':
            multiple_data = my_socket.recv(1024)
        else:
            multiple_data = client_socket.recv(1024)
        print('data =', multiple_data)
        if multiple_data:
            for data in multiple_data.decode('utf-8').rstrip().split('\n'):
                print(data)
                x, y, color_r, color_g, color_b = [int(s) for s in data.split()]
                if my_type == 'client':    
                    draw_point((x, y), (color_r, color_g, color_b))
                else:
                    recv_point_on_server((x, y), (color_r, color_g, color_b))
    except BlockingIOError:
        pass


def main():
    init_display()
    init_network()

    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == MOUSEMOTION:
                print('motion')
                if pygame.mouse.get_pressed()[0]:
                    send_point_to_server(pygame.mouse.get_pos())

        watch_socket()
        pygame.display.flip()
        Clock.tick(FPS)


if __name__ == '__main__':
    main()