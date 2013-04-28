import datetime


class Person(object):
    pass


class Male(Person):
    pass


class Vitalik(Male):
    '''Define basic API every handsome guy can rely on.  Some methods are
    also available to girls.
    '''

    def spend_the_night(self, date: datetime.date, location, caller: Person, 
                        supper_proposal={('spaghetti', 'initiator'), 
                                         ('bolognese', 'Vitalik')}) -> bool:
        pass  # hey, it's just a Python keyword

    def nearest_days_with_free_space(self, caller: Male) -> list:
        pass

    def go_for_a_walk(self, date: datetime.date, caller: Person):
        pass

    def explain_programming_topic(self, caller: Person, topic):
        pass