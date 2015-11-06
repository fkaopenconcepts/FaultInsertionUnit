<p style="text-align: justify;">In the case of test scenarios, e.g. for system tests, the "Fault Insertion Unit" (short: FIU) can be used to represent irregular system behavior. For its integration into a test scenario, the signal path from the stimulus to the DUT needs to be disrupted and diverted through the FIU so that the FIU is the last element on the signal path to the DUT and thus can regulate and modify the actual input.</p>
<p style="text-align: justify;"><a href="http://opensource.kuefen.de/wp-content/uploads/2015/10/Schlechttest.png"><img class="alignnone wp-image-241 size-full" src="http://opensource.kuefen.de/wp-content/uploads/2015/10/Schlechttest.png" alt="" width="636" height="324" /></a></p>
<p style="text-align: justify;">This allows an easy and central way for the integration into the test construction and offers flexible and comprehensive modifications. All modifications, which are already implemented and available, can be found in an overview <a href="http://opensource.kuefen.de/systemvalidierung/fehleraufschaltung/fehleraufschaltung/beschreibung-der-fehlerbloecke/">here</a>. If needed, the fault blocks can be extended and modified easily.</p>
<p style="text-align: justify;">Theoretically the chronological order in which the different fault blocks can modify the signal is variable. Although some modifications will not have the desired effect on the signal when there are also other modifications which work "against them". So the Fault Insertion Unit already offers the most convenient orders for the different signal types which are illustrated below:</p>
<p style="text-align: justify;"><span style="text-decoration: underline;">Modifications and order for continuous signals:</span></p>
<p style="text-align: justify;"><a href="./images/Continuous.png"><img class="alignnone wp-image-69" src="./images/Continuous.png" alt="Continuous" width="604" height="110" /></a></p>
<p style="text-align: justify;"><span style="text-decoration: underline;">Modifications and order for digital signals:</span></p>
<p style="text-align: justify;"><a href="./images/Digital.png"><img class="alignnone wp-image-70" src="./images/Digital.png" alt="Digital" width="407" height="110" /></a></p>
<p style="text-align: justify;"><span style="text-decoration: underline;">Modifications and order for quantized signals:</span></p>
<p style="text-align: justify;"><a href="./images/Case.png"><img class="alignnone wp-image-68" src="./images/Case.png" alt="Case" width="217" height="110" /></a></p>
<p style="text-align: justify;">The implementation of the Fault Insertion Unit is currently available for:</p>

<ul style="text-align: justify;">
	<li><a href="http://opensource.kuefen.de/systemvalidierung/fehleraufschaltung/fehleraufschaltungc-code-basiert/">C++ based simulations</a></li>
	<li><a href="http://opensource.kuefen.de/systemvalidierung/fehleraufschaltung/simulink-basiert/">Simulink based simulations</a></li>
	<li><a href="http://opensource.kuefen.de/systemvalidierung/fehleraufschaltung/ni-veristand-basiert/">VeriStand based simulations</a></li>
</ul>
<p style="text-align: justify;">Others are planned and will be available soon.</p>
