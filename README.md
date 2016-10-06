# networked-cubesats
Code from Summer 2015 CubeSat prototyping project, posted here for exhibition purposes. 
Latest version July 31, 2015. Uploaded October 2016.
Intention: Develop a system of networked CubeSats that can intercommunicate wirelessely through a remote protocol, 
sending collected information to a ground station (a computer) for processing.

Code for three separate Arduino boards, representing the motherboards for each of the three CubeSats.
  1. A "control" 
  2. A "radiation" experiment
  3. A "weather" experiment

Boards #2 and #3 possess sensors on them for collecting relevant scientific data (radiation levels, temperatures, humidity, etc) 
for its topic. Board #1 serves as a "control" satellite, which receives the data from satellites #2 and #3 and transmits it back to the 
computer based ground station.

  • Satellites communicate over the XBee Wireless Protocol, flexible for many numbers of satellites.
  • Satellites are self-sufficient with this code, and can operate without any connection to a computer
 
  
