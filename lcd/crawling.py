# -*- coding: utf-8 -*-
import sys
import os
import request
import urllib
import bs4
from urllib2 import urlopen

reload(sys)
sys.setdefaultencoding('utf8')
location = '서울'
enc_location = urllib.quote(location + '+날씨')

url = 'https://search.naver.com/search.naver?ie=utf8&query='+ enc_location


page = urlopen(url)
html = page.read()
soup = bs4.BeautifulSoup(html,'html5lib')
temperature = soup.find('p', class_='info_temperature').find('span', class_='todaytemp').text
weather = soup.find('ul', class_='info_list').find('p', class_='cast_txt').text
weather = weather.split(',')
message2 = ''
# print(weather[0])
# weather_list = list(weather)
# weather_list = weather_list.split(',')
# print(weather_list)
#
# print(weather)
print(location)
print(temperature)
print(weather[0])
if weather[0] == '맑음' :
    weather[0] = 'sunny'
elif weather[0] == '구름많음':
    weather[0] = 'cloudy'
elif weather[0] == '구름조금':
    weather[0] ='cloudy'
elif weather[0] == '흐림':
    weather[0] = 'cloudy'
elif weather[0] == '안개':
    weather[0] = 'foggy'
elif weather[0]== '비':
    weather[0] = 'rain'
    message2 = "'Check Umbrella!'"
elif weather[0] == '소나기':
    weather[0] = 'short_rain'
    message2 = "'Check Umbrella!'"
elif weather[0] == '눈':
    weather[0] = 'Snow'
    message2 = "'Outside SnowDay'"

else :
    weather[0] = "'Check Phone'"

if int(temperature) < -5:
    message2 = "'Very Very Cold!'"
elif int(temperature) > 30:
    message2 = "'Very Very Hot!'"
                               

message = 'seoul:'+temperature+':'+weather[0]

os.system("./lcdtest "+message+" "+message2)

