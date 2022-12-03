#From https://github.com/hbldh/bleak
import asyncio
from bleak import BleakScanner
from bleak import BleakClient
from bleak.exc import BleakError


MAGNETIC_SENSOR_DATA_SERVICE_UUID = "00002a24-1234-1000-8000-00805f9b34fb"
LED_SERVICE_UUID = "00002a24-4321-1000-8000-00805f9b34fb"

async def main():
    devices = await BleakScanner.discover()
    i = 0
    for d in devices:
        print(i,"-",d)
        i+=1
    escolha = -1
    while escolha < 0 or escolha > len(devices):
        escolha = int(input("Escolha um device: "))

    blutooth = devices[escolha]
    arduino = BleakClient(blutooth)
    print("Conectando para",blutooth)

    #client = BleakClient(address)
    
    await arduino.connect(timeout = 30)

    print(arduino.is_connected)

    #print(len(arduino.services))
    #data = await arduino.read_gatt_char(MAGNETIC_SENSOR_DATA_UUID)
    #print("Data: {0}".format("".join(map(int, data))))
    #except Exception as e:
        #print(e)
    #finally:
    #    await arduino.disconnect()

    while arduino.is_connected:
        data = await arduino.read_gatt_char(MAGNETIC_SENSOR_DATA_SERVICE_UUID)
        print("Data: {0}".format(list(map(int, data))))
        
        #await arduino.write_gatt_char(LED_SERVICE_UUID, bytearray([0x01]))
        #await asyncio.sleep(1.0)
        #await arduino.write_gatt_char(LED_SERVICE_UUID, bytearray([0x02]))
        #await asyncio.sleep(1.0)

asyncio.run(main())