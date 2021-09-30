# traffic-collision-avoidance-system

## Predicates

-----------------------------------------

To generate test cases, I created a simple "mask" system:

24: `Own_Tracked_Alt < Other_Tracked_Alt`

T: - - - 0 - 1 - - - - - -

F: - - - 0 - 0 - - - - - -


29: `Other_Tracked_Alt < Own_Tracked_Alt`

T: - - - 1 - 0 - - - - - -

F: - - - 0 - 0 - - - - - -

52: `Alt == 0`

T: - - - - - - 0 - - - - -

F: - - - - - - 1 - - - - -

54: `Alt == 1`

T: - - - - - - 1 - - - - -

F: - - - - - - 0 - - - - -

57: `Alt == 2`

T: - - - - - - 2 - - - - -

F: - - - - - - 0 - - - - -

61: `Alt == 3`

T: - - - - - - 3 - - - - -

F: - - - - - - 0 - - - - -

74: `Climb_Inhibit`

T: - - - - - - - - - - - 1

F: - - - - - - - - - - - 0

83: `Inhibit_Biased_Climb() > Down_Separation`

T: - - - - - - - 0 - - - 1

F: - - - - - - - 0 - - - 0

~~87: `!(Own_Below_Threat()) || ((Own_Below_Threat()) && (!(Down_Separation >= ALIM())))`~~

~~91: `Own_Above_Threat() && (Cur_Vertical_Sep >= 300 ) && (Up_Separation >= ALIM())`~~

~~107: `Own_Below_Threat() && (Cur_Vertical_Sep >= 300) && (Down_Separation >= ALIM())`~~

~~111: `!(Own_Above_Threat()) || ((Own_Above_Threat()) && (Up_Separation >= ALIM())`~~

~~125: `High_Confidence && (Own_Tracked_Alt_Rate <= 600) && (Cur_Vertical_Sep > 600)`~~

126: `Other_Capability == 1`

T: - - - - - - - - - - 1 -

F: - - - - - - - - - - 0 -

127: `Two_of_Three_Reports_Valid && Other_RAC == 0`

T: - - 1 - - - - - - 0 - -

F: - - 0 - - - - - - 0 - -

~~131: `(enabled && ((tcas_equipped && intent_not_known) || !tcas_equipped)`~~

133: `Non_Crossing_Biased_Climb() && Own_Below_Threat()`

T: 300 - - 1 - 0  - - - - - - 17000 - - - -

F: 0 - - 1 - 0  - - - - - -  -1 - - - -

134: `Non_Crossing_Biased_Descend() && Own_Above_Threat()`

T: 300 - - 1 - 0 - - 17000 - - -

F: 0 - - 0 - 0 - - 17000 - - -

136: `need_upward_RA && need_downward_RA`

T: 300 - 0 0 1 0 - - 0 - - -

F: 0 - 0 0 1 0 - - 0 - - -

140: `need_upward_RA`

T: 300 - 0 0 1 0 - - 0 - - -

F: 0 - 0 0 1 0 - - 0 - - -

143: `need_downward_RA`

T: 300 - - 1 - 0 - - 17000 - - -

F: 0 - - 1 - 0 - - 17000 - - -

157: `argc < 13`

T: 0 0 0 0 0 0 0 0 0 0 0 0 0 0

F:  0 0 0

### Simplify

-----------------------------------------

a: `Own_Below_Threat()`

b: `Down_Separation`

c: `ALIM()`

d: `Own_Above_Threat()`

e: `Cur_Vertical_Sep`

f: `Up_Separation`


87: `!(a) || ((a) && (!(b >= c)))`

T: 300 - - 0 - 0 - - 0 - - -

F: 300 - - 0 - 0 - - 16435 - - -


91: `d && (e >= 300) && (f >= c)`

T: 300 - - 1 - 0  - - - - - - 17000 - - - -

F: 0 - - 1 - 0  - - - - - -  -1 - - - -

107: `a && (e >= 300) && (b >= c)`

T: 300 - - 1 - 0 - - 17000 - - -

F: 0 - - 0 - 0 - - 17000 - - -

111: `!(d) || ((d) && (f >= c)`

T: - - - 0 - 0 - - - - - -

F: - - - 1 - 0 - - - - - -

125: `High_Confidence && (Own_Tracked_Alt_Rate <= 600) && (e > 600)`

T: 601 1 - - 1 - - - - - - -

F: 0 1 - - 1 - - - - - - -

131: `(enabled && ((tcas_equipped && intent_not_known) || !tcas_equipped)`

T: - - - - - - - - - - 0 -

F: 0 1 - - 1 - - - - - - -


