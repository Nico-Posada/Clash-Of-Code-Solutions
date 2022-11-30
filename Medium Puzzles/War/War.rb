@war_deck_ready_p1 = []
@war_deck_ready_p2 = []

# Epic recurrsion
def WAR
  begin
    p1_war_deck = [ @p1.shift, @p1.shift, @p1.shift ]
    p2_war_deck = [ @p2.shift, @p2.shift, @p2.shift ]

    war_card_p1 = @p1.shift
    war_card_p2 = @p2.shift

    @war_deck_ready_p1 << p1_war_deck << war_card_p1
    @war_deck_ready_p2 << p2_war_deck << war_card_p2

    if war_card_p1 == war_card_p2
      return WAR()
    else
      return war_card_p1 > war_card_p2
    end
  rescue
    puts "PAT"
    exit
  end
end

normalize = -> (card) {card.first.gsub(/[JQKA]/){$&==?J?'11':$&==?Q?'12':$&==?K?'13':'14'}.to_i}

n = gets.to_i
@p1 = n.times.map{normalize[ gets.scan(/(\d{1,2}|.)./)[0] ]}
m = gets.to_i
@p2 = m.times.map{normalize[ gets.scan(/(\d{1,2}|.)./)[0] ]}

rounds = 0
while @p1.size > 0 && @p2.size > 0
  @card_p1 = @p1.shift
  @card_p2 = @p2.shift

  if @card_p1 > @card_p2
    @p1 << @card_p1 << @card_p2
  elsif @card_p2 > @card_p1
    @p2 << @card_p1 << @card_p2
  else
    @war_deck_ready_p1 << @card_p1
    @war_deck_ready_p2 << @card_p2
    p1_win = WAR()

    if p1_win
      @p1 << @war_deck_ready_p1 << @war_deck_ready_p2
      @p1.flatten!
    else
      @p2 << @war_deck_ready_p1 << @war_deck_ready_p2
      @p2.flatten!
    end

    @war_deck_ready_p1 = []
    @war_deck_ready_p2 = []
  end

  rounds += 1
end

puts [@p1.size > 0 ? 1 : 2, rounds]*' '
