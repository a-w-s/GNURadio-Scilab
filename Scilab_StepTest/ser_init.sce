// To load the serial toolbox and open the serial port
exec loader.sce

handl = openserial("/dev/ttyUSB0","9600,n,8,0")

//the order is : port number,"baud,parity,databits,stopbits"
// here 9 is the port number
// In the case of SBHS, stop bits = 0, so it is not specified in the function here
// Linux users should give this as "/dev/ttyUSB0""9600,n,8,0"

if (ascii(handl) ~= [])
  disp("COM Port Opened");
end
