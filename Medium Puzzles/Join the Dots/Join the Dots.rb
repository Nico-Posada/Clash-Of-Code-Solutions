def connect(start, go_to)
    @grid[ start[1] ][ start[0] ] = ?o
    shouldStar = -> (char, expected) { "X+*".include?(char) || 
                                     ("-|".include?(char) && "\\/".include?(expected)) ||
                                     ("-|".include?(expected) && "\\/".include?(char)) }

    while (start[0]-go_to[0]) | (start[1]-go_to[1]) != 0
        x = go_to[0] <=> start[0]
        y = go_to[1] <=> start[1]

        start[0] += x
        start[1] += y

        result = ''
        chr = @grid[ start[1] ][ start[0] ]

        if x == 0
            result = chr == ?- ? ?+ : ?|
        elsif y == 0
            result = chr == ?| ? ?+ : ?-
        elsif x*y > 0
            result = chr == ?/ ? ?X : ?\\
        else
            result = chr == ?\\ ? ?X : ?/
        end

        result = ?* if (shouldStar.call(chr, result))
        @grid[ start[1] ][ start[0] ] = result
    end
    @grid[ go_to[1] ][ go_to[0] ] = ?o
end

public def results
    self.map! do |c|
        c = c == ?. ? ' ' : c
    end
    puts self.join.rstrip
end

letters = [*1..9].join+[*?A..?Z]*''

h, w = gets.split.map &:to_i
points = {}
@grid = []

h.times do |y|
  row = gets.chomp.chars
  pts = (0...w).find_all{ letters.include? row[_1] }
  pts.each{|x| points.store(row[x], [x, y]) }
  @grid << row
end
points = points.sort_by{ letters.index(_1[0]) }.to_h

for i in 1...points.size
    start = points[ letters[i-1] ]
    go_to = points[ letters[i]   ]

    connect(start, go_to)
end
@grid.map &:results
