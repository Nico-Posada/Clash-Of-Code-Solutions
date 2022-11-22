base_str = " " + `sed 1d` # extra space is to account for possibility of inputted string being a palindrome
temp_str = ""
idx = 0

while 1
    temp_str = base_str[idx] + temp_str
    result = base_str + temp_str
    if result == result.reverse
        puts idx
        return
    end
    idx += 1
end
