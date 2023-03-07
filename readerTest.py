import unittest
from io import StringIO
from receiver import calculate_sma_and_extremes

class TestMovingAverage(unittest.TestCase):
    
    def test_calculate_sma_and_extremes(self):
        input_data = "Temperature: = 15.0 - Soc: = 22.0\nTemperature: = 12.0 - Soc: = 18.0\nTemperature: = 10.0 - Soc: = 10.0\nTemperature: = 25.0 - Soc: = 50.0\nTemperature: = 20.0 - Soc: = 75.0\nTemperature: = 30.0 - Soc: = 90.0\n"
        expected_output = {'SMA': [18.6, 23.0, 28.6, 45.8], 'min': 10.0, 'max': 90.0}
        with StringIO() as fake_out:
            # Redirect stdout to capture output
            import sys
            sys.stdout = fake_out
            
            # Call function with test data
            calculate_sma_and_extremes(input_data)
            
            # Get output from stdout
            output = fake_out.getvalue().strip()
            
            # Convert output string to dictionary
            output_dict = eval(output)
            
            # Assert expected output matches actual output
            self.assertEqual(expected_output, output_dict)


if __name__ == '__main__':
    unittest.main()

