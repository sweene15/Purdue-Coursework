"""linearAlgWrk URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.11/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import include, url
from django.contrib import admin
from core.views import MainView, InputFormView, SizeFormView, EntryNewFormView, RemoveFormView, ViewerFormView
from django.contrib.auth import views as auth_views
from core import views

urlpatterns = [
    url(r'^login/$', auth_views.login, {'template_name': 'core/login.html'}, name='login'),
    url(r'^logout/$', auth_views.logout, {'next_page': '/login'}, name='logout'),
    url(r'^admin/', admin.site.urls),
    url(r'^$', MainView.as_view(), name='main'),
    url(r'^input/submit', InputFormView.as_view(), name='input'),
    url(r'^size/submit', SizeFormView.as_view(), name='size'),
    url(r'^entry/submit', EntryNewFormView.as_view(), name='new_entry'),
    url(r'^remove/submit', RemoveFormView.as_view(), name='remove'),
    url(r'^viewer/submit', ViewerFormView.as_view(), name='viewer'),
    url(r'^signup/$', views.signup, name='signup'),
]
