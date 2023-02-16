import io
import sys
import unittest
import csv
from sender import send_data_from_csv

class TestSender(unittest.TestCase):
    def test_send_data_from_csv(self):
        # Capture the output of the send_data_from_csv function
        output = io.StringIO()
        sys.stdout = output

        send_data_from_csv('sensor_data.csv')

        # Reset the output stream
        sys.stdout = sys.__stdout__

        # Verify the output is in the correct format
        output_data = output.getvalue().strip().split('\n')
        headers = output_data[0].split(',')
        self.assertEqual(headers, ['Timestamp', 'Sensor Value'])
        for i, row in enumerate(output_data[1:]):
            values = row.split(',')
            self.assertEqual(float(values[0]), i * 0.5)
            self.assertTrue(0 <= int(values[1]) <= 100)

if __name__ == '__main__':
    unittest.main()
