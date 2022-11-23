n = gets.to_i
commands = *$<

values = [nil] * n

# fill in values with predetermined values
commands.each_with_index do |cmd, i|
    operation, arg_1, arg_2 = cmd.split
    next if operation != "VALUE" || arg_1[?$]

    values[i] = arg_1.to_i
end

# do the rest, least optimized but whatever
while 1
    should_repeat = false
    commands.each_with_index do |cmd, i|
        operation, arg_1, arg_2 = cmd.split
        next if operation == "VALUE" && !arg_1[?$]

        arg_1=values[arg_1[/\d+/].to_i] if arg_1=~/\$/
        arg_2=values[arg_2[/\d+/].to_i] if arg_2=~/\$/
        if arg_1.nil? || arg_2.nil?
            should_repeat = true
            next
        end
        a,b=[arg_1,arg_2].map &:to_i
        values[i] = [a,a+b,a-b,a*b]['VASM'.index operation[0]]
    end

    break if should_repeat == false
end
puts values
