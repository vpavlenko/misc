import datetime


class Person(object):
    pass


class Male(Person):
    pass


class Vitalik(Male):
    '''
    Define basic API every smart tender interesting handsome/beautiful human can
    rely on.
    '''

    def spend_the_night(self, date: datetime.date, location, caller: Person,
                        what_about_supper) -> bool:
        '''
        Consider famous meeting format: walking before, cooking and eating after
        or eating in the cafe, chatting, hugging, kissing, watching a film, 
        playing musical instruments, roller skating.  After: maybe mutual masturbation
        with elements of oral sex, maybe other kinds of sexual activity,
        then sleeping together (better naked).  There is nothing new under the sun.
        '''
        pass

    def nearest_days_with_free_space(self, caller: Person) -> list:
        return []  # sorry but I live with my family

    def nearest_days_with_free_time(self, caller: Person) -> list:
        pass

    def go_for_a_walk(self, date: datetime.date, caller: Person):
        pass

    def explain_programming_topic(self, caller: Person, topic):
        pass  # the most popular method here
