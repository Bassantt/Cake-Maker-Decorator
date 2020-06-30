# Cake-Maker-Decorator

1- Making the cake. To make the cake you need to add the following components in the following order
a. Eggs: open the eggs valve for 500 Milliseconds. All valves are controlled by a servo motor
b. Start the mixer. The mixer is considered as a stepper motor. The mixer speed is 10 revolutions per
second.
c. After 5 mixer rotations, Open the vanilla valve for 100 milliseconds. And keep rotating the mixer
for 4 more rotations. The mixer should not stop while adding the vanilla.
d. Open the sugar valve for 200 milliseconds.
e. Make another 10 mixer rotations.
f. Now, the mixer speed will be reduced to the half. It should be 5 revolutions per second.
g. Do the following three times
i. Open the flour valve for 100 milliseconds
ii. make 4 mixer rotations

2- Baking the cake:
a. Move the production line using another stepper motor for one full rotation
b. The cake is now in the oven, open the heater (replaced by a red LED) for 1 second.
c. Move the production line again for one full rotation
d. Stop every thing for one second. (The cake needs to cool down)
3- Cake decoration:
a. There is a mechanical arm used to decorate the cake.
b. This arm consists of one servo motors to move the arm and two valves (these to valves only are
replaced by two LEDs Red and Yellow) to open the raspberry cream or pineapple cream.
c. The cake stand is rotating using a stepper motor. Therefore, decorating the cake is just like writing
data to hard disk. Except that, data is written only to side 0 / platter 0, Review to hard disk lecture
to understand the decoration method.
d. The user is able to select between 4 different very simple decorations using four keys keypad.
