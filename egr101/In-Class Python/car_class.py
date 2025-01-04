class Car():
    def __init__(self, make, model, year):
        """Initialize car properties"""
        self.make = make
        self.model = model
        self.year = year
        self.odometer = 0;

    def get_description(self):
        """Return formatted description of the car."""
        long_name = str(self.year) + ' ' + self.make + ' ' + self.model
        return long_name.title()

    def read_odometer(self):
        """Print the car mileage."""
        print('This car has ' + str(self.odometer) + ' miles on it.')

    def update_odometer(self, mileage):
        """Updates odometer mielage."""
        self.odometer = mileage



class Electric_Car(Car):
    def __init__(self, make, model , year):
        super().__init__(make, model, year)
        self.battery = 'full'
