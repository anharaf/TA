import pika
import sys
import serial

usbport = '/dev/ttyACM1'

# Set up serial baud rate
ser = serial.Serial(usbport, 9600, timeout=1) 


credentials = pika.PlainCredentials('anharaf', 'anhar1234')
parameters = pika.ConnectionParameters('192.168.43.132',
                                       5672,
                                       '/',
                                       credentials)

connection = pika.BlockingConnection()
channel = connection.channel()

channel.queue_declare(queue='anhar1')

def callback(ch, method, properties, body):
	print(body)
	ser.write(body)
channel.basic_consume(callback,
                      queue='anhar1',no_ack=True)

print(' [*] Waiting for input. To exit press CTRL+C')
channel.start_consuming()
