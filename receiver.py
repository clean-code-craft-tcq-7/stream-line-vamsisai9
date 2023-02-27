WINDOW_SIZE = 5  
def calculate_sma(data):
    """
    Calculates the simple moving average of the last WINDOW_SIZE values in the data list
    """
    if len(data) < WINDOW_SIZE:
        return None
    else:
        return sum(data[-WINDOW_SIZE:]) / WINDOW_SIZE


min_value = float('inf')
max_value = float('-inf')


last_values = []

while True:
    try:
       
        input_str = input().strip()

       
        temperature, soc = [float(x.split('=')[1].strip()) for x in input_str.split('-')]

       
        last_values.append(temperature)

        #  calculate the SMA and update min/max values
        if len(last_values) >= WINDOW_SIZE:
            sma = calculate_sma(last_values)
            if sma is not None:
                if sma < min_value:
                    min_value = sma
                if sma > max_value:
                    max_value = sma

           
            last_values.pop(0)

            
            print(f"SMA: {sma:.2f}, Min: {min_value:.2f}, Max: {max_value:.2f}")
        
    except KeyboardInterrupt:
       
        break
    except:
        
        continue
