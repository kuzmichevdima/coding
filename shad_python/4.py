def print_lyrics():
    numbers = ["Ten", "Nine", "Eight", "Seven", "Six", "Five", "Four", "Three", "Two", "One", "no"]
    for i in range(len(numbers) - 1):
        get_fin = lambda s : 's' if s != "One" else ''
        s = str(numbers[i] + " green bottle" + get_fin(numbers[i]) + " hanging on the wall,\n")
        print(s, s, 
"""And if one green bottle should accidentally fall,
There’ll be """, numbers[i + 1].lower(), " green bottle", get_fin(numbers[i + 1]), " hanging on the wall.\n", sep='')
print_lyrics()
