from django.db import models
from django.utils import timezone
from django import forms
from django.contrib.auth.models import User
from django.db.models.signals import post_save
from django.dispatch import receiver
# Create your models here.

INPUT_CHOICES = (
    ('add', 'ADD'),
    ('multiply', 'MULTIPLY'),
    ('rref', 'RREF'),
    ('determinant', 'DETERMINANT'),
    ('inverse', 'INVERSE'),
)
SIZE_CHOICES = (
    ('1', '1'),
    ('2', '2'),
    ('3', '3'),
    ('4', '4'),
    ('5', '5'),
)
class Profile(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE)
    
    @receiver(post_save, sender=User)
    def create_user_profile(sender, instance, created, **kwargs):
        if created:
            Profile.objects.create(user=instance)

    @receiver(post_save, sender=User)
    def save_user_profile(sender, instance, **kwargs):
        instance.profile.save()




class Varia(models.Model):
    user = models.ForeignKey(User, null=True)
    name =  models.CharField(max_length = 12, null=True)
    row_length = models.IntegerField(null=True)
    col_length = models.IntegerField(null=True)
    row1element1 = models.IntegerField(null = True)
    row1element2 = models.IntegerField(null = True)
    row1element3 = models.IntegerField(null = True)
    row1element4 = models.IntegerField(null = True)
    row1element5 = models.IntegerField(null = True)
    row2element1 = models.IntegerField(null = True)
    row2element2 = models.IntegerField(null = True)
    row2element3 = models.IntegerField(null = True)
    row2element4 = models.IntegerField(null = True)
    row2element5 = models.IntegerField(null = True)
    row3element1 = models.IntegerField(null = True)
    row3element2 = models.IntegerField(null = True)
    row3element3 = models.IntegerField(null = True)
    row3element4 = models.IntegerField(null = True)
    row3element5 = models.IntegerField(null = True)
    row4element1 = models.IntegerField(null = True)
    row4element2 = models.IntegerField(null = True)
    row4element3 = models.IntegerField(null = True)
    row4element4 = models.IntegerField(null = True)
    row4element5 = models.IntegerField(null = True)
    row5element1 = models.IntegerField(null = True)
    row5element2 = models.IntegerField(null = True)
    row5element3 = models.IntegerField(null = True)
    row5element4 = models.IntegerField(null = True)
    row5element5 = models.IntegerField(null = True)
    class Meta:
        unique_together= ["user", "name"]

    pass


class Input(models.Model):
    col_size = models.CharField(max_length=1, choices=SIZE_CHOICES)
    row_size = models.CharField(max_length=1, choices=SIZE_CHOICES)
    input_type = models.CharField(max_length=12, choices=INPUT_CHOICES)
    queried_date = models.DateTimeField(default = timezone.now)
    #choice = forms.ModelChoiceField(queryset=Varia.objects.filter(name = (request.user.username)))
    def __str__(self):
        return self.input_type

class Output(models.Model):
    startVar = models.ForeignKey('Varia', related_name = 'startVar', null=True, on_delete=models.CASCADE,)
    endVar = models.ForeignKey('Varia', related_name = 'endVar', null=True, on_delete=models.CASCADE,) 



