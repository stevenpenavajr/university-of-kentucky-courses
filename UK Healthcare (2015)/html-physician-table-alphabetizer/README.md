# HTML Physician Name Alphabetizer
A program to sort an HTML table alphabetically by last name of physicians/doctors with titles in the text, such as "First Last, PhD". I was tasked with reordering a large table filled with doctors, but the title in the string made it a bit tricky. So, I implemented this tool myself to get the job done.

### Date of Creation
July 2016

### Version
1.0

### Usage Instructions

Make sure your text file for input looks just like this:

```sh
<table border="0" style="width: 549px; height: 788px;"><tbody>

<tr><td style="background-color: #ffffff;"><img src="/sites/default/files/aroor.jpg" width="180" height="225" style="box-shadow: 1px 1px 5px rgba(0, 0, 0, 0.98); -moz-box-shadow: 1px 1px 5px rgba(0, 0, 0, 0.98); -webkit-box-shadow: 1px 1px 5px rgba(0, 0, 0, 0.98); padding: 0px;" /></td><td style="background-color: #ffffff;"><h3><a href="https://neurology.med.uky.edu/neurology-sushanth-aroor-mbbs">Sushanth Aroor, MBBS</a></h3><h3>PGY-4</h3><h3>&nbsp;</h3></td></tr>
<tr><td style="background-color: #ffffff;"><img src="/sites/default/files/barnes_0.jpg" width="180" height="225" style="box-shadow: 1px 1px 5px rgba(0, 0, 0, 0.98); -moz-box-shadow: 1px 1px 5px rgba(0, 0, 0, 0.98); -webkit-box-shadow: 1px 1px 5px rgba(0, 0, 0, 0.98); padding: 0px;" /></td><td style="background-color: #ffffff;"><h3><a href="https://neurology.med.uky.edu/neurology-ben-barnes">Benjamin Barnes, MD</a></h3><h3>PGY-2</h3><h3>&nbsp;</h3></td></tr>

</tbody></table>
```

Your table rows must be ONE LINE EACH! The program finds ", MD", or ", PhD" and scans backwards to single out last name.

The program will create a text file with your specified name with results for copying/pasting into your HTML file.

### Screenshots

![Alt text](screenshot1.png?raw=true "Optional Title")
![Alt text](screenshot2.png?raw=true "Optional Title")
