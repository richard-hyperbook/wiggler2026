'declarando las variables
Dim HiScore
Dim GameOn
Dim Players
Dim UpBall 
Dim Ball 
Dim PL(1)
Dim UpLight(1)
Dim Score(2)
Dim TempScore(2)
Dim Credit
Dim Credit1(2)
Dim Credit2(2)
Dim Credit3(2)
Dim Tilted
Dim Tilts
Dim Up
Dim x
dim bb
dim bonus
Dim BonusX
Dim BonusLamp(20)
Dim ebcount


Set UpLight(1) = Up1

Set BonusLamp(1) = Light1
Set BonusLamp(2) = Light2
Set BonusLamp(3) = Light3
Set BonusLamp(4) = Light4
Set BonusLamp(5) = Light5
Set BonusLamp(6) = Light6
Set BonusLamp(7) = Light7
Set BonusLamp(8) = Light8
Set BonusLamp(9) = Light9
Set BonusLamp(10) = Light10
Set BonusLamp(11) = Light11
Set BonusLamp(12) = Light12
Set BonusLamp(13) = Light13
Set BonusLamp(14) = Light14
Set BonusLamp(15) = Light15
Set BonusLamp(16) = Light16
Set BonusLamp(17) = Light17
Set BonusLamp(18) = Light18
Set BonusLamp(19) = Light19
Set BonusLamp(20) = Light20

'iniciando
init
sub init()
    Score(1) = 0
    Up = 1
    textBoxGO.Text = "fin de partida"
End Sub

'funciones del teclado, flippers, plunger, echar moneda y todo eso

Sub Table1_KeyDown(ByVal keycode)

	If keycode = PlungerKey Then
		Plunger.PullBack
	End If

	If keycode = LeftFlipperKey Then
	  If GameOn = TRUE then
		If Tilted = FALSE then
		LeftFlipper.RotateToEnd
		PlaySound "Flipper"
        End If
      End If
	End If
    
	If keycode = RightFlipperKey Then
	  If GameOn = TRUE then
		If Tilted = FALSE then
		RightFlipper.RotateToEnd
		PlaySound "Flipper"
        End If
      End If
	End If
	
	If keycode = LeftTiltKey Then
		Nudge 90, 2
		TiltCheck
	End If
    
	If keycode = RightTiltKey Then
		Nudge 270, 2
		TiltCheck
	End If
    

	
	If keycode = LeftTiltKey Then
		Nudge 90, 2
		TiltCheck
	End If
    
	If keycode = RightTiltKey Then
		Nudge 270, 2
		TiltCheck
	End If





	If keycode = CenterTiltKey Then
		Nudge 0, 2
		TiltCheck
	End If

   	if keycode = 6 then 
          if Credit < 9 then
     		Credit = Credit + 1
			
     		Playsound "coin3"
        end if
		CredBox.Text = Credit
		
	end if
    
	if keycode = 2 then
        if Credit > 0 then
           If GameOn = FALSE and Players = 0 then
              StartGame
              Exit Sub
           End If   
             If Players < 1 and Score(1) = 0 then
                Players = Players + 1
                Credit = Credit - 1
                CredBox.Text = Credit 
                End If
           End If  
        end if      
End Sub

Sub Table1_KeyUp(ByVal keycode)

	If keycode = PlungerKey Then
		Plunger.Fire
	PlaySound "Plunger"
	End If
    
	If keycode = LeftFlipperKey Then
      If GameOn = TRUE then
		LeftFlipper.RotateToStart
    End If
	End If
    
	If keycode = RightFlipperKey Then
      If GameOn = TRUE then
		RightFlipper.RotateToStart
    End If
	End If

	
End Sub

'el tilt la falta

Sub TiltCheck
   If Tilted = FALSE then
      If Tilts = 0 then
         Tilts = Tilts + int(rnd*100)
         TiltTimer.Enabled = TRUE
      Else   
         Tilts = Tilts + int(rnd*100)
      End If   
      If Tilts >= 225 and Tilted = FALSE then
         LeftFlipper.RotateToStart
         RightFlipper.RotateToStart
         Tilted = TRUE 
         TiltTimer.Enabled = FALSE 
         TiltBox.Text = "falta"
         PlaySound "ROBuzz"
       GameOn = True
       EndBall = True
      End If  
   End If
End Sub

Sub TiltTimer_Timer()
    If Tilts > 0 then
       Tilts = Tilts - 1
        Else
       TiltTimer.Enabled = FALSE
    End If
End Sub

'iniciando el juego, las variables, los rodillos y todo lo demas


Sub StartGame
	Players = 1
	bb=0 'estado de la bola
    Up = 1
    UpLight(1).State = 1
    Credit = Credit - 1
    CredBox.Text = Credit
    PlaySound "inicio"
    Tilted = FALSE
    Tilts = 0
    TiltBox.Text = ""
    textBoxGO.Text = ""
    GameOn = TRUE
    For x = 1 to 10
    Next
    For x = 1 to 2
    Score(x) = 0
    Credit1(x) = FALSE
    Credit2(x) = FALSE
    Next
	light27.state=1
	bumper1.state=0
    EMReel1.ResettoZero 
	EMReel3.ResettoZero	
	EMReel3.AddValue 1
    ResetTimer.Enabled = TRUE
	Ebcount=0 		
	Ball=1 	

End Sub


Sub ResetTimer_Timer()
    ResetTimer.Enabled = FALSE
    Ball = 1
    CurrTho = 0
    CurrHun = 0
    CurrTen = 0
    BallReleaseTimer.Enabled = TRUE
End Sub  

Sub BallReleaseTimer_Timer()
       BallReleaseTimer.Enabled = FALSE
       kicker4.createball.image="Webball"
       kicker4.kick 090,2
       BallUp = TRUE  
		sacabola.state=1
End Sub

sub kicker3_hit()
    kicker3.DestroyBall
end sub

sub gate1_hit()
	playsound "Gate5"
end sub


'el asunto de los bonus

Sub BonusHole_Hit()
     BonusHole.DestroyBall
     BonusHoleTimer.Enabled = TRUE
  	Bonusholetimer.interval= 1400
End Sub



Sub BonusHoleTimer_Timer()
    BonusHoleTimer.Enabled = FALSE
    If Tilted = FALSE then
         BonusCount
     End If
     Drain_Hit()
End Sub


Sub BonusCount()
    If Bonus < 20 then
    BonusTimer.Enabled = TRUE 
  	Bonustimer.interval= 200
  End If
End Sub

'los bonos depende del estado de las luces

Sub BonusTimer_timer()
    If Bonus > 0  then
       PlaySound "_bell10"
        For x = 1 to BonusX
       Next
       Bonus = Bonus - 1
       LightBonus 
       //+++++++++++++++++++++++++++++++++++++++++++++++++++++++
		if dbonuslight.state=1 then 
      	AddScore 3000
      	playsound "bing3"
		end if
      	if dbonuslight.state=1 then 
      	AddScore 2000
      	playsound "bing3"
		end if
      	if dbonuslight.state=0 then
      	Addscore 1000
      	playsound "jet4"
      	end if
    Else
       BonusTimer.Enabled = FALSE
    End If
End Sub

Sub LightBonus
    For X = 1 to 20
       BonusLamp(x).State = LightStateOff
    Next
       If Bonus > 0 and Bonus < 21 then
       BonusLamp(bonus).State = LightStateOn
       End If
   If Bonus = 20 then
       BonusLamp(20).State = LightStateOn
      End If
End Sub

'el asunto del drain de cuando comienza una nueva bola iniciando todo

Sub Drain_Hit()
    BallUp = FALSE
    Drain.DestroyBall
    PlaySound "drain"
	bb = 0
    Tilts = 0
    TiltBox.Text = ""
    PlayerDelayTimer.Enabled = TRUE
	dbonuslight.state=0
	bumper1.state=0
	'luces del bono
	light1.state=0
	light2.state=0
	light3.state=0
	light4.state=0
	light5.state=0
	light6.state=0
	light7.state=0
	light8.state=0
	light9.state=0
	light10.state=0
	'doble bono
	light11.state=0
	light12.state=0
	light13.state=0
	light14.state=0
	light15.state=0
	light16.state=0
	light17.state=0
	light18.state=0
	light19.state=0
	light20.state=0
	light21.state=0 'luz que avisa el comienzo del doble bono

	'dianas naranjas
	light22.state=0 'A
	light23.state=0 'B
	light24.state=0 'C
	light25.state=0 'D

	light26.state=0 '50000 con luz
	light27.state=1 'apaga bumper
	sacabola.state=0 'shoot again 
	
	'coladeros
	light28.state=0
	light29.state=0

	'luz del hoyo especial
	light30.state=0
	'luz verde de arriba
	light31.state=0

	'luces de las mediocircunferencias
	light32.state=0
	light33.state=0	
	light34.state=0 'luz del activa bumper
End Sub
	
sub addbonus()
bonus=bonus+1
if light1.state=0 and bonus=1 then
light1.state=1

exit sub
end if
if light1.state=1 and bonus=2 then
light2.state=1
exit sub
end if
if light2.state=1 and bonus=3 then
light3.state=1 
exit sub
end if
if light3.state=1 and bonus=4 then
light4.state=1
exit sub
end if
if light4.state=1 and bonus=5 then 
light5.state=1
exit sub
end if
if light5.state=1 and bonus=6 then
light6.state=1
exit sub
end if
if light6.state=1 and bonus=7 then
light7.state=1
exit sub
end if
if light7.state=1 and bonus=8 then
light8.state=1
light29.state=1
exit sub
end if
if light8.state=1 and bonus=9 then
light9.state=1
light28.state=1
exit sub
end if
if light9.state=1 and bonus=10 then
light10.state=1
light30.state=1
exit sub
end if
'doble bonos
if light10.state=1 and bonus=11 then
light11.state=1
light21.state=2
light26.state=1
exit sub
end if
if light11.state=1 and bonus=12 then
light12.state=1
exit sub
end if
if light12.state=1 and bonus=13 then
light13.state=1 
exit sub
end if
if light13.state=1 and bonus=14 then
light14.state=1
exit sub
end if
if light14.state=1 and bonus=15 then 
light15.state=1
exit sub
end if
if light15.state=1 and bonus=16 then
light16.state=1
exit sub
end if
if light16.state=1 and bonus=17 then
light17.state=1
exit sub
end if
if light17.state=1 and bonus=18 then
light18.state=1
exit sub
end if
if light18.state=1 and bonus=19 then
light19.state=1
exit sub
end if
if light19.state=1 and bonus=20 then
light20.state=1
exit sub
end if

end sub
	




Sub PlayerDelayTimer_Timer()
    Tilted = FALSE 
    Tilts = 0
    TiltBox.Text = "" 
     PlayerDelayTimer.Enabled = FALSE
      UpLight(Up).State = LightStateOff 
    If extra =0 then
       Up = Up + 1 
       IF Up> Players then
        Ball = Ball + 1
        Up = 1
       End If   
    End if
    extra = extra - 1
    If Ball > 5 then
       GameOn = FALSE
       GameOver
      Else
      Emreel3.setvalue ball
       BallReleaseTimer.Enabled = TRUE
    End If
End Sub

Sub GameOver()
	LeftFlipper.RotateToStart
	RightFlipper.RotateToStart
	PlaySound "fx_ballrel"
    textBoxGO.Text = "fin de partida"
	light11.state=0
	light12.state=0
	light27.state=0
    For X = 1 to Players
      If Score(x) > hiscore then
          hiscore = Score(X)
		awardspecial()
      End If
	next
    Players = 0
	
End Sub
  
'Triggers
'Lo que hace accionar la bola
sub trigger1_hit() 
	bb=1
    playsound"ballin"
end sub

sub trigger2_hit()
	If light32.state=0 then
	light32.state=1
	playsound "score500"
	addscore(500)
	exit sub
	end if
	If light32.state=1 then
	light32.state=2
	light34.state=2
	bumper1.state=1
	light27.state=0
	playsound "score500"
	addscore(500)
	exit sub
	end if
	If light32.state=2 then
	light32.state=1
	bumper1.state=0
	light34.state=0
	light27.state=1
	playsound "score500"
	addscore(500)
	exit sub
	end if
end sub
sub trigger3_hit()
	If light33.state=0 then
	light33.state=1
	light32.state=0
	light34.state=0
	playsound "score500"
	addscore(500)
	exit sub
	end if
	If light33.state=1 then
	playsound "score500"
	light33.state=2
	light34.state=2
	bumper1.state=1
	light27.state=0
	addscore(500)
	exit sub
	end if
	If light33.state=2 then
	light33.state=1
	playsound "score500"
	addscore(500)
	exit sub
	end if
end sub
sub trigger4_hit()
	if sacabola.state=1 then
		sacabola.state=0
	end if
end sub

sub trigger5_hit()
	addscore(500)
	playsound "Score500"
end sub

Sub trigger6_hit()
	if light28.state=1 then
		addscore(500)
		Playsound "Knocke"
		Credit = Credit + 1
		CredBox.Text = Credit
	end if	
end sub
Sub trigger7_hit() 
	if light29.state=1 then
		addscore(500)
		Playsound "Knocke"
		Credit = Credit + 1
		CredBox.Text = Credit
	end if	
end sub

'Diana

sub Wall10_hit()
	if light30.state=1  then
		Playsound "Knocke"
		Credit = Credit + 1
		CredBox.Text = Credit
		addscore (10000)
		light30.state=0
	else
		playsound "ROBuzz"
		addscore(100)
	end if
end sub

sub Wall11_hit()
	if light30.state=1  then
		Playsound "Knocke"
		Credit = Credit + 1
		CredBox.Text = Credit
		addscore (10000)
		light30.state=0
	else
		playsound "ROBuzz"
		addscore(100)
	end if
end sub

Sub wall16_hit()
light22.state=1
addscore(100)
if light1.state=0  then
light1.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light1.state=1  then
light2.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light2.state=1  then
light3.state=1 
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light3.state=1  then
light4.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light4.state=1  then 
light5.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light5.state=1  then
light6.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light6.state=1 then
light7.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light7.state=1  then
light8.state=1
light29.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light8.state=1  then
light9.state=1
light28.state=1
playsound "Score10"
addscore(1000)
addbonus()
exit sub
end if
if light9.state=1 then
light10.state=1
light30.state=1
playsound "Score3000"
addscore(1000)
addbonus()
exit sub
end if

'doble bonos
if light10.state=1  then
light11.state=1
light21.state=2
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light11.state=1  then
light12.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light12.state=1  then
light13.state=1 
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light13.state=1  then
light14.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light14.state=1  then 
light15.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light15.state=1  then
light16.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light16.state=1 then
light17.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light17.state=1  then
light18.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light18.state=1  then
light19.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light19.state=1 then
light20.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if

end sub


sub wall17_hit()
light23.state=1
addscore(100)
if light1.state=0  then
light1.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light1.state=1  then
light2.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light2.state=1  then
light3.state=1 
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light3.state=1  then
light4.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light4.state=1  then 
light5.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light5.state=1  then
light6.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light6.state=1 then
light7.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light7.state=1  then
light8.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light8.state=1  then
light9.state=1
playsound "Score10"
addscore(1000)
addbonus()
exit sub
end if
if light9.state=1 then
light10.state=1
light30.state=1
playsound "Score3000"
addscore(1000)
addbonus()
exit sub
end if

'doble bonos
if light10.state=1  then
light11.state=1
light21.state=2
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light11.state=1  then
light12.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light12.state=1  then
light13.state=1 
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light13.state=1  then
light14.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light14.state=1  then 
light15.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light15.state=1  then
light16.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light16.state=1 then
light17.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light17.state=1  then
light18.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light18.state=1  then
light19.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light19.state=1 then
light20.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
end sub

sub wall18_hit()
addscore(100)
light24.state=1
if light1.state=0  then
light1.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light1.state=1  then
light2.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light2.state=1  then
light3.state=1 
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light3.state=1  then
light4.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light4.state=1  then 
light5.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light5.state=1  then
light6.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light6.state=1 then
light7.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light7.state=1  then
light8.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light8.state=1  then
light9.state=1
playsound "Score10"
addscore(1000)
addbonus()
exit sub
end if
if light9.state=1 then
light10.state=1
light30.state=1
playsound "Score3000"
addscore(1000)
addbonus()
exit sub
end if

'doble bonos
if light10.state=1  then
light11.state=1
light21.state=2
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light11.state=1  then
light12.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light12.state=1  then
light13.state=1 
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light13.state=1  then
light14.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light14.state=1  then 
light15.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light15.state=1  then
light16.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light16.state=1 then
light17.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light17.state=1  then
light18.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light18.state=1  then
light19.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light19.state=1 then
light20.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
end sub

sub wall19_hit()
addscore(100)
light25.state=1
if light1.state=0  then
light1.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light1.state=1  then
light2.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light2.state=1  then
light3.state=1 
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light3.state=1  then
light4.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light4.state=1  then 
light5.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light5.state=1  then
light6.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light6.state=1 then
light7.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light7.state=1  then
light8.state=1
playsound "Score10"
addscore(100)
addbonus()
exit sub
end if
if light8.state=1  then
light9.state=1
playsound "Score10"
addscore(1000)
addbonus()
exit sub
end if
if light9.state=1 then
light10.state=1
light30.state=1
playsound "Score3000"
addscore(1000)
addbonus()
exit sub
end if

'doble bonos
if light10.state=1  then
light11.state=1
light21.state=2
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light11.state=1  then
light12.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light12.state=1  then
light13.state=1 
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light13.state=1  then
light14.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light14.state=1  then 
light15.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light15.state=1  then
light16.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light16.state=1 then
light17.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light17.state=1  then
light18.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light18.state=1  then
light19.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
if light19.state=1 then
light20.state=1
playsound "Score3000"
addscore(2000)
addbonus()
exit sub
end if
end sub

'flippers

Sub Wall14_Slingshot()
	PlaySound "reelclick"
	addscore(10)
End Sub


Sub wall15_Slingshot()
	PlaySound "reelclick"
	addscore(10)
End Sub

'spinner

sub spinner1_hit()
	addscore(100)
	playsound "spinner"
end sub

'Bumpers

sub bumper1_hit() 
	if bumper1.state=1 then
	addscore(1000)
	bumper1.force=6
	playsound "bumper100"
	else
	addscore(100)
	playsound "score100"
	end if
End Sub

'hoyo del especial

sub kicker1_hit() 
	If Tilted = FALSE then
    End If
	if  light30.state=1 then
		Playsound "Knocke"
		Credit = Credit + 1
		CredBox.Text = Credit
		addscore (10000)
		light30.state=0
		kicker1.TimerEnabled=True
		kicker1.TimerInterval=1000
	
	else
	BonusCount
	AddScore (200)
	kicker1.TimerEnabled=True
	kicker1.TimerInterval=1000
	end if
	exit sub
End Sub

Sub kicker1_Timer()
	kicker1.TimerEnabled=False
	kicker1.Kick 300,10 
	PlaySound "Ballhit"
End Sub



'partida extra
Sub AwardSpecial()
	Playsound "Knocke"
    Credit = Credit + 1
   CredBox.Text = Credit
	
End Sub


Sub AddScore(val) 
  If Tilted = FALSE then
    Score(Up) = Score(Up) + val
    DisplayScore
    AddReel val
  End If  
End Sub    

Sub AddReel(Pts)
   Select Case Up
   Case 1
   EmReel1.AddValue Pts
   End Select  
 
End Sub

'partidas extras al superar los handicaps de puntuación

Sub DisplayScore()
        	If Score(Up) >= 100000 And Credit1(Up)=false Then
            AwardSpecial
		    Credit1(Up)=true
	    End If
        	If Score(Up) >= 150000 And Credit2(Up)=false Then
            AwardSpecial
		    Credit2(Up)=true
	    End If
	     If Score(Up) >= 200000 And Credit3(Up)=false Then
            AwardSpecial
		    Credit3(Up)=true
	    End If	
End Sub

' guardar el record
sub savehs
	Dim FileObj
	Dim ScoreFile
	Set FileObj=CreateObject("Scripting.FileSystemObject")
	If Not FileObj.FolderExists(UserDirectory) then 
		Exit Sub
	End if
	Set ScoreFile=FileObj.CreateTextFile(UserDirectory & "tab.txt",True)
		ScoreFile.WriteLine hiscore
		ScoreFile.Close
	Set ScoreFile=Nothing
	Set FileObj=Nothing
end sub

sub loadhs
    
'cargar el record	
	Dim FileObj
	Dim ScoreFile
    dim temp1
    Set FileObj=CreateObject("Scripting.FileSystemObject")
	If Not FileObj.FolderExists(UserDirectory) then 
		Exit Sub
	End if
	If Not FileObj.FileExists(UserDirectory & "tab.txt") then
		Exit Sub
	End if
	Set ScoreFile=FileObj.GetFile(UserDirectory & "tab.txt")
	Set TextStr=ScoreFile.OpenAsTextStream(1,0)
		If (TextStr.AtEndOfStream=True) then
			Exit Sub
		End if
		temp1=TextStr.ReadLine
		TextStr.Close
	    HiScore = CDbl(temp1)
	    Set ScoreFile=Nothing
	    Set FileObj=Nothing
end sub 