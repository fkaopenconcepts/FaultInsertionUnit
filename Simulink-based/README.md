<p style="text-align: justify;">In the use case of Simulink, the Fault Insertion Unit-Toolbox exists in form of a library, from which the appropriate FIU for the different signal types (continuous, digital, case) can be used. The FIU only needs to be interconnected between input signal and the actual simulationsystem/DUT. Subsequent the parameters of the wanted errors should be configured and modified either manually or with the provided config-blocks. The exact procedure will be described in detail by a simple simulation setup.</p>

<h2 style="text-align: justify;">Example Setup</h2>
<p style="text-align: justify;">(<a href="http://opensource.kuefen.de/downloads/">download</a>)</p>
<p style="text-align: justify;">In this example we will work with a simple simulation setup of a transfer function. We want to observe how it will react on possible input errors. In case of simplification the here used input signal is just a sine with the amplitude 2. The transfer function is given by:</p>
<p style="text-align: justify;"><span style="color: #000000;">[latex size=0 color=000000 background=ffffff]\displaystyle G(s) = s * \frac{1+0.2s^{-1}}{1}[/latex]</span></p>
<p style="text-align: justify;">The system and the related response are shown in the following :</p>


[caption id="attachment_98" align="alignnone" width="578"]<a href="http://opensource.kuefen.de/wp-content/uploads/2015/10/SimulationExample1.png"><img class="wp-image-98 size-full" src="http://opensource.kuefen.de/wp-content/uploads/2015/10/SimulationExample1.png" alt="SimulationExample" width="578" height="189" /></a> Simple simulation setup[/caption]
<p style="text-align: justify;">Now we want to add our FIU to see how the system reacts in "bad cases". Therefor the FIU-block (here: continuous) just needs to be put between our transfer function and the signal source. So the source should be connected with the input and the filter connected with output of the FIU then. After the intrusion of the FIU the new system should look like this:</p>


[caption id="attachment_101" align="alignnone" width="501"]<a href="http://opensource.kuefen.de/wp-content/uploads/2015/10/SimulationExampleAndFIU1.png"><img class="wp-image-101 size-full" src="http://opensource.kuefen.de/wp-content/uploads/2015/10/SimulationExampleAndFIU1.png" alt="SimulationExampleAndFIU" width="501" height="235" /></a> Modified simulation setup[/caption]
<p style="text-align: justify;">Now we just need to configure the parameters of the different error blocks and we are good to go. They can be either set variable by other functions or inputs or set by the provided config-block which sets the parameters to constant values. To keep it as simple as possible we will use the second way in the following. So we just connect the block "Continuous_Config" with the remaining inputs of the FIU.</p>
<p style="text-align: justify;">To change the values of the error parameters we need to go into the config-block and change the related constants there. By default all errors are deactivated and the new system would show the same behavior like the setup without the FIU.</p>

<h3 style="text-align: justify;">Configuration of the parameters</h3>
<p style="text-align: justify;">If you take a look into the config-block you will find the parameters, defined as constants, on the left side used to configure the errors. The variable "Mode" which defines how many and which errors will be used is set automatically and does not need to be considered in our example. In case you do not want to use the config-block, also the port "Mode" need to be actuated. For the input of this port a value of the type "unit8" is needed, where for every error you want to use another bit needs to be set. This correlates to adding the related hexadecimal values. In the following table you can see which value represents which value:</p>

<table>
<tbody>
<tr>
<td width="77">Fault:</td>
<td width="77">Freeze</td>
<td width="77">FixedValue</td>
<td width="77">Delay</td>
<td width="77">Drift</td>
<td width="77">Offset</td>
<td width="77">Slewrate</td>
<td width="77">Noise</td>
</tr>
<tr>
<td width="77">Bit:</td>
<td width="77">0</td>
<td width="77">1</td>
<td width="77">2</td>
<td width="77">3</td>
<td width="77">4</td>
<td width="77">5</td>
<td width="77">6</td>
</tr>
<tr>
<td width="77">Value:</td>
<td width="77">0x01</td>
<td width="77">0x02</td>
<td width="77">0x04</td>
<td width="77">0x08</td>
<td width="77">0x10</td>
<td width="77">0x20</td>
<td width="77">0x40</td>
</tr>
</tbody>
</table>
<p style="text-align: justify;">Though in our case it is only necessary to set the rest of the constants. These parameters deactivate the correspondent error in case they are set to zero. And in case they are not zero they represent the following depending on each block:</p>
<p style="text-align: justify;"><span style="text-decoration: underline;">Freeze</span>: value unequal zero activates the freezing-block</p>
<p style="text-align: justify;"><span style="text-decoration: underline;">FixedValue</span>: sets the signal the this value</p>
<p style="text-align: justify;"><span style="text-decoration: underline;">Delay</span>: delays the signal by this time (in seconds)</p>
<p style="text-align: justify;"><span style="text-decoration: underline;">DriftValue</span>: maximum drift value the signal will approach</p>
<p style="text-align: justify;"><span style="text-decoration: underline;">DriftTime</span>: needed time to reach the maximum drift value</p>
<p style="text-align: justify;"><span style="text-decoration: underline;">Offset</span>: adds this value to the signal</p>
<p style="text-align: justify;"><span style="text-decoration: underline;">Slewrate</span>: sets maximum slope (positive and negative)</p>
<p style="text-align: justify;"><span style="text-decoration: underline;">NoiseRate</span>: describes rate/pattern of the noise</p>
<p style="text-align: justify;"><span style="text-decoration: underline;">NoiseAmplitude</span>: sets the amplitude of the noise</p>
<p style="text-align: justify;">So, if we want to test now how the system will react to a delay of 2 seconds and noise, we just change the constant value of "Set Delay" to "2" and the values of "Set NoiseRate" and "Set NoiseAmplitude" to "10" an "1". Afterwards the error-prone signal would look like this, compared to the original signal:</p>


[caption id="attachment_47" align="alignnone" width="653"]<a href="http://opensource.kuefen.de/wp-content/uploads/2015/10/SourceSignal_vs_SignalWithFaults.png"><img class="wp-image-47 size-full" src="http://opensource.kuefen.de/wp-content/uploads/2015/10/SourceSignal_vs_SignalWithFaults.png" alt="" width="653" height="266" /></a> original signal vs. modified signal[/caption]
<p style="text-align: justify;">Like this, all different kinds of scenarios could be realised by adding or removing and changing of the parameters of the error-blocks. If we now look into our output signal with the current fault insertion we will see this signal:</p>


[caption id="attachment_44" align="alignnone" width="322"]<a href="http://opensource.kuefen.de/wp-content/uploads/2015/10/OutputSignal.png"><img class="wp-image-44 size-full" src="http://opensource.kuefen.de/wp-content/uploads/2015/10/OutputSignal.png" alt="OutputSignal" width="322" height="199" /></a> new output signal[/caption]
<p style="text-align: justify;">Now it is quite easy to see that our system has an instable behavior in case of quickly changing values (noise), since the output signal values have such big magnitudes. Since this is a bad charateristic for a system in the most cases, we would already found one problem with just adding a bit of noise. If we analyse our transfer function we will see that this is caused by the d-term in our function. But since in reality it is most often way more complicated to analyse a given system or just not possible because you might not know the exact mathematical function of it, this toolbox provides an easy tool to test your system also in "bad cases".</p>
