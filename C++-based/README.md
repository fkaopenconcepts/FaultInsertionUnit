<p style="text-align: justify;">In the use case of C++, the Fault Insertion Unit-Toolbox exists in form of one cpp- and one hpp-file. They contain all necessary functions and auxiliaries to realise the "bad-case" scenario in a simulation.</p>
<p style="text-align: justify;">The following simple example of a C++ simulation program will show, how exactly the installation of the FIU program works.</p>


<hr />

[alt tag](./images/Input.png)

<h2 style="text-align: justify;"><strong>Example Program
</strong></h2>
<p style="text-align: justify;">Our example program, which we want to test on tolerance for input errors, does  for reasons of simplification nothing else than calculating the slope between the current and the last signal value.</p>
<p style="text-align: justify;">With the predefined input signal (left, blue) the output signal would look like the following (right, red):</p>

<p style="text-align: justify;"><a href="https://raw.githubusercontent.com/fkaopenconcepts/FaultInsertionUnit/test/C%2B%2B-based/images/Input.png"><img class="alignnone wp-image-77" src="https://raw.githubusercontent.com/fkaopenconcepts/FaultInsertionUnit/test/C%2B%2B-based/images/Input.png" alt="Input" width="299" height="224" /></a> <a href="https://raw.githubusercontent.com/fkaopenconcepts/FaultInsertionUnit/test/C%2B%2B-based/images/Output.png"><img class="alignnone wp-image-79" src="https://raw.githubusercontent.com/fkaopenconcepts/FaultInsertionUnit/test/C%2B%2B-based/images/Output.png" alt="Output" width="299" height="224" /></a></p>

<p style="text-align: justify;">The main loop of our program contains the following code segements where the signal processing is happening:</p>

<pre><span style="color: #000000;">Signal = Input[ControlVariable];  <span style="color: #339966;">// input values -&gt; signal</span>
Signal = GetSlope(Signal);        <span style="color: #339966;">// DUT</span>
Output[ControlVariable] = Signal; <span style="color: #339966;">// modified signal -&gt; output</span>
</span></pre>
<p style="text-align: justify;">In the first line the signal gets the value out of an array of predefined values. Then our DUT gets this signal and will modify it depending on its function (here: getting the slope). And in the last line the modified signal will be stored in an output variable.</p>
<p style="text-align: justify;">So now, if we want to use the FIU in our program process, we need to include the header file (.hpp) in our program head.</p>
<p style="text-align: justify;">Next, the global constant "SAMPLETIME" in the .hpp-file should be modified to a value that describes the time (in seconds) which is needed for one loop walkthrough. This is necessary for functions like delaying the signal.</p>
<p style="text-align: justify;">Now we did all required preparations to create our first FIU-blocks. With the command "tFIU FIU_1;" a struct of the type "tFIU" with the name "FIU_1" will be created. It is possible to create as many FIUs as desired like this, to realize for example the modification and observation of many signals in different scenarios. Each FIU contains all error blocks available for the actual signal, though all of them are not activated or configurated by default. At first the type of the used signal (continuous, digital, case) should be set. Since the default type already is continuous it is not mandatory in our case, but in general you could change it with the following macro:</p>

<pre><span style="color: #000000;"><span style="color: #800080;">SET_TYP</span>(fiu, typ);         <span style="color: #339966;">// fiu = Name of the created FIU
                           // typ = {CONTINUOUS, DIGITAL, CASE}</span></span></pre>
<p style="text-align: justify;">To change the configuration of the single error block the following macros can be used:</p>

<pre><span style="color: #000000;"><span style="color: #800080;">SET_FREEZE</span>(fiu, enable);
<span style="color: #800080;">SET_FIXEDVALUE</span>(fiu, enable, value);
<span style="color: #800080;">SET_DELAY</span>(fiu, enable, delay);
<span style="color: #800080;">SET_DRIFT</span>(fiu, enable, value, time);
<span style="color: #800080;">SET_OFFSET</span>(fiu, enable, value);
<span style="color: #800080;">SET_SLEWRATE</span>(fiu, enable, value);
<span style="color: #800080;">SET_NOISE</span>(fiu, enable, amplitude, pattern);</span></pre>
<p style="text-align: justify;">The first parameter should always be the name of the FIU which you want to modify (here: "FIU_1") and the second one whether the block is activated or not (with: "ENABLED" or "DISABLED"). In case of more than two parameters, there are also fault-specific configuration options, like for example the offset value at the offset-block.</p>
<p style="text-align: justify;">So now we want to add a noise pattern to our input signal to check whether our DUT is able to cope with it or not. Therefore we need to configure the noise-block like this:</p>

<pre><span style="color: #800080;">SET_NOISE</span><span style="color: #000000;">(FIU_1,</span> <span style="color: #800080;">ENABLED</span><span style="color: #000000;">, 1, 1);</span></pre>
<p style="text-align: justify;">With that our FIU is configured and ready to be used. The only thing missing is now the intrusion of the FIU into the input signal. For this we need to add the provided function "double InsertFaults (double Signal, tFIU* FIU)", which returns the error-prone signal, into our main loop of the program. The main loop looks like this then:</p>

<pre><span style="color: #000000;">Signal = Input[ControlVariable];      <span style="color: #339966;">// input values -&gt; signal</span>
Signal = InsertFaults(Signal, &amp;FIU_1);<span style="color: #339966;">// intrusion of FIU</span>
Signal = GetSlope(Signal);            <span style="color: #339966;">// DUT</span>
Output[ControlVariable] =  Signal;    <span style="color: #339966;">// modified signal -&gt; output</span>
</span></pre>
<p style="text-align: justify;">Now the input/output signals will look like this:</p>
<p style="text-align: justify;"><a href="https://raw.githubusercontent.com/fkaopenconcepts/FaultInsertionUnit/test/C%2B%2B-based/images/InputWithFaults.png"><img class="wp-image-78 alignnone" src="https://raw.githubusercontent.com/fkaopenconcepts/FaultInsertionUnit/test/C%2B%2B-based/images/InputWithFaults.png" alt="InputWithFaults" width="299" height="224" /></a><a href="https://raw.githubusercontent.com/fkaopenconcepts/FaultInsertionUnit/test/C%2B%2B-based/images/OutputWithFaults.png"><img class="wp-image-80 alignnone" src="https://raw.githubusercontent.com/fkaopenconcepts/FaultInsertionUnit/test/C%2B%2B-based/images/OutputWithFaults.png" alt="OutputWithFaults" width="299" height="224" /></a></p>
<p style="text-align: justify;">You could still identify the input pattern like this if you now that there was noise added; the output signal instead looks completly random and has not much in common with the "good case" output.</p>
<p style="text-align: justify;">Analog this could be implemented and tested with any of the available errors and combinations of them and different scenarios could be tested, also by changing parameter of the blocks.</p>
