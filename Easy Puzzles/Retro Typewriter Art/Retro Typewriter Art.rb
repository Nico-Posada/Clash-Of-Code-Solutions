commands = gets.chomp.split.map{ |cmd| cmd.scan(/(\d+)(sp|bS|sQ|.)|(nl)/)[0] }
commands.each do |count, cmd, nl|
    count = count.to_i
    case cmd
    when 'sp' then print ' '*count
    when 'bS' then print '\\'*count
    when 'sQ' then print '\''*count
    else  !nl.nil? ? puts() : print(cmd*count)
    end
end
