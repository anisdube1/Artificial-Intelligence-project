import math
import random

class Node:
    def __init__(self, name, lat, long):
        self.name = name
        self.lat = lat
        self.long = long

def distance(n1, n2):
    lat1 = n1.lat*3.14159/180.0
    long1 = n1.long*3.14159/180.0
    lat2 = n2.lat*3.14159/180.0
    long2 = n2.long*3.14159/180.0
    dlon = long2 - long1
    dlat = lat2 - lat1
    a = (math.sin(dlat/2))**2 + math.cos(lat1) * math.cos(lat2) * (math.sin(dlon/2))**2
    c = 2 * math.atan2( math.sqrt(a), math.sqrt(1-a))
    d = 3961 * c
    return d

def total_dis(cities):
    dist =0;
    for i in range(0, len(cities)-1):
        dist = dist + distance(cities[i], cities[i+1])
    dist+= distance(cities[0], cities[len(cities)-1])
    return dist


def successor(city):
    cities = city[:]
    bound1 = math.floor(len(cities)*random.random())
    bound2 = math.floor(len(cities)*random.random())
    if(bound1>bound2):
        upper = bound1
        lower = bound2
    else:
        upper = bound2
        lower = bound1

    while(lower<=upper):
        temp = cities[lower]
        cities[lower] = cities[upper]
        cities[upper] = temp
        lower= lower+1
        upper = upper-1

    return cities

def printcity(cities):
    for city in cities:
        print(city.name)

def input():
    cities =[]
    input = open("input.txt", "r")
    for city in input:
        city_lat_lan = city.split()
        cities.append(Node(city_lat_lan[0], float(city_lat_lan[1]), float(city_lat_lan[2])))
    return cities

if __name__ == "__main__":
    cities = input()
    iteration = 0
    initial_temp = 60
    print("Before Total Distance", total_dis(cities))
    while 1:
        temp = initial_temp - 0.001*iteration
        if(temp<=0):
            break
        curr_dist = total_dis(cities)
        cities_next=successor(cities)
        next_dist = total_dis(cities_next)
        if(next_dist<curr_dist):
            cities=cities_next
        else:
            prob = math.exp((curr_dist - next_dist)/temp)
            ran = random.random()
            if (ran < prob):
                cities=cities_next
        iteration= iteration+1

    print("After Total Distance", total_dis(cities), "Iterations", iteration)
    printcity(cities)