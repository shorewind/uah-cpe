# inclass hw 2.1
# time to communicate to deep space probe

# speed of light c

SPEED_OF_LIGHT_kmPS = 300000

# query the user

dist_km_string = input('How far is the probe ? [km] ')

# convert the string to a floating point

dist_km = float(dist_km_string)

# time in sec

time_sec = dist_km/SPEED_OF_LIGHT_kmPS

time_min = time_sec/60

time_hr = time_min/60


# display time in hours

time_hr_string = str(time_hr)

print('The time in hrs is ' + time_hr_string)

