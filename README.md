# traffic-collision-avoidance-system

## Predicates

24: `Own_Tracked_Alt < Other_Tracked_Alt`

29: `Other_Tracked_Alt < Own_Tracked_Alt`

52: `Alt == 0`

54: `Alt == 1`

57: `Alt == 2`

61: `Alt == 3`

74: `Climb_Inhibit`

83: `Inhibit_Biased_Climb() > Down_Separation`

~~87: `!(Own_Below_Threat()) || ((Own_Below_Threat()) && (!(Down_Separation >= ALIM())))`~~

~~91: `Own_Above_Threat() && (Cur_Vertical_Sep >= 300 ) && (Up_Separation >= ALIM())`~~

~~107: `Own_Below_Threat() && (Cur_Vertical_Sep >= 300) && (Down_Separation >= ALIM())`~~

~~111: `!(Own_Above_Threat()) || ((Own_Above_Threat()) && (Up_Separation >= ALIM())`~~

~~125: `High_Confidence && (Own_Tracked_Alt_Rate <= 600) && (Cur_Vertical_Sep > 600)`~~

126: `Other_Capability == 1`

127: `Two_of_Three_Reports_Valid && Other_RAC == 0`

~~131: `(enabled && ((tcas_equipped && intent_not_known) || !tcas_equipped)`~~

133: `Non_Crossing_Biased_Climb() && Own_Below_Threat()`

134: `Non_Crossing_Biased_Descend() && Own_Above_Threat()`

136: `need_upward_RA && need_downward_RA`

140: `need_upward_RA`

143: `need_downward_RA`

157: `argc < 13`

### Simplify
a: `Own_Below_Threat()`

b: `Down_Separation`

c: `ALIM()`

d: `Own_Above_Threat()`

e: `Cur_Vertical_Sep`

f: `Up_Separation`

g: `e >= 300`

h: `b >= c`

i: `f >= c`



87: `!(a) || ((a) && (!(h)))`

91: `d && (g) && (i)`

107: `a && (g) && (h)`

111: `!(d) || ((d) && (i)`

125: `High_Confidence && (Own_Tracked_Alt_Rate <= 600) && (e > 600)`

131: `(enabled && ((tcas_equipped && intent_not_known) || !tcas_equipped)`


