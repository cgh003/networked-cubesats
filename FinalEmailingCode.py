import time
import smtplib
from xlrd import open_workbook
from threading import Timer
from Tkinter import *

def email():

    mail = smtplib.SMTP('smtp.gmail.com', 587)
    mail.ehlo()
    mail.starttls()
    
    FROM = 'quailinterns@gmail.com'

    TO = ["ume14gg@gmail.com"] # must be a list
    
    sub = "Email"

    # Prepare actual message

    message = 'Subject: %s\n\n%s' % (SUBJECT, TEXT)
    mail.login('quailinterns@gmail.com', 'quail123')

    mail.sendmail('quailinterns@gmail.com', 'danielshihtiger@gmail.com' , message)

    mail.close()
    print "email sent"


def assign():
    global row,col,yes,x,y,z,lux,uv,lat,longg,timer,TEXT,SUBJECT,l
    wb = open_workbook('/Users/Daniel/Desktop/Test6.xlsx')
    row = 1
    col = 1
    yes = 60
    x = 0
    y = 0
    z = 0
    lux = 0
    uv = 0
    lat = 0
    longg = 0
    timer =0 
    TEXT = "This message was sent with Python's smtplib."
    SUBJECT = "Hello!"
    l = 100
    
def reread():
    global wb
    wb = open_workbook('/Users/Daniel/Desktop/Test6.xlsx')
    print "reread"

def kindex():
    global xmax,xmin,kIndex,TEXT,SUBJECT
    if xmax - xmin ==0 and xmax-xmin < 5 :
        TEXT = "K index level 0"
        Subject = "K Index Alert"
        #email()
    elif xmax - xmin > 5 and xmax-xmin < 10 :
        TEXT = "K index level 1"
        Subject = "K Index Alert"
        #email()
    elif xmax - xmin > 10 and xmax-xmin < 20 :
        TEXT = "K index level 2"
        Subject = "K Index Alert"
        #email()
    elif xmax - xmin > 20 and xmax-xmin < 40 :
        TEXT = "K index level 3"
        Subject = "K Index Alert"
        #email()
    elif xmax - xmin > 40 and xmax-xmin < 70 :
        TEXT = "K index level 4"
        Subject = "K Index Alert"
        #email()
    elif xmax - xmin > 70 and xmax-xmin < 120 :
        TEXT = "K index level 5"
        Subject = "K Index Alert"
        email()
    elif xmax - xmin > 120 and xmax-xmin < 200 :
        TEXT = "K index level 6"
        Subject = "K Index Alert"
        email()
    elif xmax - xmin > 200 and xmax-xmin < 330 :
        TEXT = "K index level 7"
        Subject = "K Index Alert"
        email()
    elif xmax - xmin > 330 and xmax-xmin < 500 :
        TEXT = "K index level 8"
        Subject = "K Index Alert"
        email()
    elif xmax-xmin < 500 :
        TEXT = "K index level 9"
        Subject = "K Index Alert"
        email()
    global t
    t = Timer(10.0, kindex)
    t.start()
    xmax = 0 
    xmin = 0

t = Timer(10.0, kindex)
t.start() # after 60 seconds calls the hello method
row = 1
col = 1
yes = 60
x = 0
xmax = 0
xmin = 1000
kIndex = 0
y = 0
z = 0
lux = 0
l = 100
uv = 0
lat = 0
longg = 0
TEXT = "This message was sent with Python's smtplib."
SUBJECT = "Hello!"
def code():
    print "In"
    reread()
    assign()
    global row,col,yes,x,xmax,xmin,kIndex,y,z,lux,uv,lat,longg,timer,TEXT,SUBJECT,l,wb

    while(yes==60):
        global row,col,yes,x,y,z,lux,uv,lat,longg,timer,TEXT,SUBJECT,l,wb
        try:
            print "row" ,row
            print "col" , col
            #if(s.cell_value(row,col) != ''):
            for s in wb.sheets():
                print "i hate this"
            
                x = s.cell_value(row,col)
                y = s.cell_value(row,col+1)
                z = s.cell_value(row,col+2)
                lux = s.cell_value(row,col+3)
                uv = s.cell_value(row,col+4)
                lat = s.cell_value(row,col+5)
                longg = s.cell_value(row,col+6)
                co = s.cell_value(row,col+7)
                H = s.cell_value(row,col+8)
                M = s.cell_value(row,col+9)
                Pa = s.cell_value(row,col+10)
                C = s.cell_value(row,col+11)
                F = s.cell_value(row,col+12)
                Hu = s.cell_value(row,col+13)
                print x, y, z, lux, uv, lat, longg, co, H, M, Pa, C, F, Hu
                row = row +1
                
#                 if l + 50 < lux:
#                     TEXT = 'Lux has increased drastically',l,'to',lux
#                     SUBJECT = "Lux"
#                     email()
#                     l = lux
#                 if l - 50 > lux:
#                     TEXT = 'Lux has decreased drastically',l,'to',lux
#                     SUBJECT = "Lux"
#                     email()
#                     l = lux
                
                if xmax<x :
                    xmax = x
                elif xmin>x :
                    xmin = x
                
        except IndexError:
            time.sleep(1)
            reread()
            continue
        

code()










