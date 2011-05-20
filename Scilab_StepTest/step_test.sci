global temp heat fan

function temp = step_test(heat,fan)

writeserial(handl,ascii(254)); //Input Heater, writeserial accepts                                       strings; so convert 254 into its                                        string equivalent 
writeserial(handl,ascii(heat));
writeserial(handl,ascii(253)); //Input Fan
writeserial(handl,ascii(fan));
writeserial(handl,ascii(255)); //To read Temp
sleep(100);

temp = ascii(readserial(handl)); // Read serial returns a string, so                                       convert it to its integer(ascii)                                      equivalent
temp = temp(1) + 0.1*temp(2); // convert to temp with decimal points                                     eg: 40.7

endfunction