$(document).ready(function(){

$("#date").DatePicker({
	format: 'Y-m-d',
	flat: true,
	date: $('#inputDate').val()? $('#inputDate').val(): new Date(),
	current: new Date(new Date().setMonth((new Date()).getMonth() + 1)),
	calendars: 2,
	mode: 'range',
	lastSel: false,
	starts: 1,
	lang : document.documentElement.lang,
	onChange: function(formated, dates){
			$('#inputDate').val(formated);	
	    } 

});

$('#inputDate').val($('#date').DatePickerGetDate(true));




});