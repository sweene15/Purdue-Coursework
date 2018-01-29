from django import forms

from .models import Input
from .models import Varia


class UserModelChoiceField(forms.ModelChoiceField):
    def label_from_instance(self, obj):
         return obj.name



class SizeForm(forms.ModelForm):
    class Meta:
        model = Input
        fields = ['row_size', 'col_size']
        labels = {
            'row_size': ('Row Size'),
            'col_size': ('Column Size')
        }

class InputForm(forms.ModelForm):
    input_1 = UserModelChoiceField(queryset=Varia.objects.all(), label = 'Variable A')
    input_2 = UserModelChoiceField(queryset=Varia.objects.all(), label = 'Variable B')
    def __init__(self, *args, **kwargs):
        username = kwargs.pop('username', None)
        super(InputForm, self).__init__(*args, **kwargs)
        if username:
            self.fields['input_1'].queryset = Varia.objects.filter(user__username=username)
            self.fields['input_2'].queryset = Varia.objects.filter(user__username=username)

    class Meta:
        model = Input
        fields = ['input_type']
        labels = {
            'input_type': ('Operation'),
        }

        
class EntryForm(forms.ModelForm):
    class Meta:
        model = Varia
        fields = ['row1element1', 'row1element2', 'row1element3', 'row1element4', 'row1element5', 
                    'row2element1', 'row2element2', 'row2element3', 'row2element4', 'row2element5',
                    'row3element1', 'row3element2', 'row3element3', 'row3element4', 'row3element5',
                    'row4element1', 'row4element2', 'row4element3', 'row4element4', 'row4element5',
                    'row5element1', 'row5element2', 'row5element3', 'row5element4', 'row5element5',
                 ]
        labels = {
            'row1element1': (''),
            'row1element2': (''),
            'row1element3': (''),
            'row1element4': (''),
            'row1element5': (''),
            'row2element1': (''),
            'row2element2': (''),
            'row2element3': (''),
            'row2element4': (''),
            'row2element5': (''),
            'row3element1': (''),
            'row3element2': (''),
            'row3element3': (''),
            'row3element4': (''),
            'row3element5': (''),
            'row4element1': (''),
            'row4element2': (''),
            'row4element3': (''),
            'row4element4': (''),
            'row4element5': (''),
            'row5element1': (''),
            'row5element2': (''),
            'row5element3': (''),
            'row5element4': (''),
            'row5element5': (''),
        }

class RemoveForm(forms.ModelForm):
    input_1 = UserModelChoiceField(queryset=Varia.objects.all(), label = 'Remove Variable')
    def __init__(self, *args, **kwargs):
        username = kwargs.pop('username', None)
        super(RemoveForm, self).__init__(*args, **kwargs)
        if username:
            self.fields['input_1'].queryset = Varia.objects.filter(user__username=username)
    class Meta:
        model = Input
        fields = ('input_1',)
        labels = {
            'input_1': ('Remove Variable')
        }

class ViewerForm(forms.ModelForm):
    input_1 = UserModelChoiceField(queryset=Varia.objects.all(), label = 'View Variable')
    def __init__(self, *args, **kwargs):
        username = kwargs.pop('username', None)
        super(ViewerForm, self).__init__(*args, **kwargs)
        if username:
            self.fields['input_1'].queryset = Varia.objects.filter(user__username=username)
    class Meta:
        model = Input
        fields = ('input_1',)
        labels = {
            'input_1': ('View Variable')
        }
class EntryNewForm(forms.ModelForm):
    def __init__(self, *args, **kwargs):
        exclude_list=kwargs.pop('exclude_list', '')
        super(EntryNewForm, self).__init__(*args, **kwargs)

        for field in exclude_list:
            del self.fields[field]
    class Meta:
        model = Varia
        fields = '__all__'
        labels = {
            'row1element1': (''),
            'row1element2': (''),
            'row1element3': (''),
            'row1element4': (''),
            'row1element5': (''),
            'row2element1': (''),
            'row2element2': (''),
            'row2element3': (''),
            'row2element4': (''),
            'row2element5': (''),
            'row3element1': (''),
            'row3element2': (''),
            'row3element3': (''),
            'row3element4': (''),
            'row3element5': (''),
            'row4element1': (''),
            'row4element2': (''),
            'row4element3': (''),
            'row4element4': (''),
            'row4element5': (''),
            'row5element1': (''),
            'row5element2': (''),
            'row5element3': (''),
            'row5element4': (''),
            'row5element5': (''), 
            }
















         


