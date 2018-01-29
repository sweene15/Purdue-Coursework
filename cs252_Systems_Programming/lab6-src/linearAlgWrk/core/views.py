import logging
from django.views.generic import TemplateView, FormView
from django.shortcuts import render, redirect
from django.contrib.auth import login, authenticate
from django.contrib.auth.forms import UserCreationForm
from  .forms import InputForm, SizeForm, EntryNewForm, RemoveForm, ViewerForm
from django.core import validators
from django.db import IntegrityError
from .models import Varia
# Create your views here.


#def MainView(request, ):
#    if request.method == 'GET':
#        input_form = InputForm(request.GET)
#        size_form = SizeForm(request.GET)
#        return render(request, 'core/index.html', {'size_form':size_form, 'input_form':input_form,})        



class MainView(TemplateView):
    template_name = 'core/index.html'
    def get(self, request, *args, **kwargs):
        if request.user.is_authenticated() == False:
            return redirect('/login')
        input_form = InputForm(self.request.GET or None, username=request.user.username)
        size_form = SizeForm(self.request.GET or None)
        remove_form = RemoveForm(self.request.GET or None, username=request.user.username)
        viewer_form = ViewerForm(self.request.GET or None, username=request.user.username)
        context = self.get_context_data(**kwargs)
        context['size_form'] = size_form
        context['input_form']= input_form
        context['remove_form']= remove_form
        context['viewer_form']= viewer_form
        if 'output0' in request.session:
            context['output0'] = request.session['output0']
            context['output1'] = request.session['output1']
            context['output2'] = request.session['output2']
            context['output3'] = request.session['output3']
            context['output4'] = request.session['output4']

        if 'array_row0' in request.session:
            context['array_row0'] = request.session['array_row0']
            context['array_row1'] = request.session['array_row1']
            context['array_row2'] = request.session['array_row2']
            context['array_row3'] = request.session['array_row3']
            context['array_row4'] = request.session['array_row4']

        if  'dataFlag' in request.session:
            data_flag = True
            context['clean_row_size'] = request.session['row_size']
            context['clean_col_size'] = request.session['col_size']
            temp_list = list()

            if(int(request.session['row_size']) < 5):
                temp_list.append('row1element5')
                temp_list.append('row2element5')
                temp_list.append('row3element5')
                temp_list.append('row4element5')
                temp_list.append('row5element5')

            if(int(request.session['row_size']) < 4):
                temp_list.append('row1element4')
                temp_list.append('row2element4')
                temp_list.append('row3element4')
                temp_list.append('row4element4')
                temp_list.append('row5element4')

            if(int(request.session['row_size']) < 3):
                temp_list.append('row1element3')
                temp_list.append('row2element3')
                temp_list.append('row3element3')
                temp_list.append('row4element3')
                temp_list.append('row5element3')

            if(int(request.session['row_size']) < 2):
                temp_list.append('row1element2')
                temp_list.append('row2element2')
                temp_list.append('row3element2')
                temp_list.append('row4element2')
                temp_list.append('row5element2')

            if(int(request.session['col_size']) < 5):
                temp_list.append('row5element1')
                temp_list.append('row5element2')
                temp_list.append('row5element3')
                temp_list.append('row5element4')
                temp_list.append('row5element5')

            if(int(request.session['col_size']) < 4):
                temp_list.append('row4element1')
                temp_list.append('row4element2')
                temp_list.append('row4element3')
                temp_list.append('row4element4')
                temp_list.append('row4element5')

            if(int(request.session['col_size']) < 3):
                temp_list.append('row3element1')
                temp_list.append('row3element2')
                temp_list.append('row3element3')
                temp_list.append('row3element4')
                temp_list.append('row3element5')

            if(int(request.session['col_size']) < 2):
                temp_list.append('row2element1')
                temp_list.append('row2element2')
                temp_list.append('row2element3')
                temp_list.append('row2element4')
                temp_list.append('row2element5')

            new_list = list(set(temp_list))
            new_list.append('user')
            new_list.append('row_length')
            new_list.append('col_length')
            #logging.warning(new_list)
            request.session['new_list'] = new_list
            new_entry_form = EntryNewForm(self.request.GET or None, exclude_list=new_list)
            context['new_entry_form'] = new_entry_form
            #del request.session['data_flag']
            #del request.session['row_size']
            #del request.session['col_size']

        return render(request, 'core/index.html', context)

class InputFormView(FormView):
    form_class = InputForm
    template_name = 'core/index.html'
    success_url = '/'
    
    def post(self, request, *args, **kwargs):
        input_form = self.form_class(request.POST)
        if input_form.is_valid():
            
            ##Get Arrays (its gonna suck)
            var1 = input_form.cleaned_data['input_1']
            var2 = input_form.cleaned_data['input_2']
            col1 = var1.row_length
            row1 = var1.col_length
            mtx1 = [ ([0] * col1) for row in range(row1) ]
            col2 = var2.row_length
            row2 = var2.col_length
            mtx2 = [ ([0] * col2) for row in range(row2) ]
            if  var1.row1element1 != None:
                mtx1[0][0] = int(var1.row1element1)
            if  var1.row1element2 != None:
                mtx1[0][1] = int(var1.row1element2)
            if  var1.row1element3 != None:
                mtx1[0][2] = int(var1.row1element3)
            if  var1.row1element4 != None:
                mtx1[0][3] = int(var1.row1element4)
            if  var1.row1element5 != None:
                mtx1[0][4] = int(var1.row1element5)
            if  var1.row2element1 != None:
                mtx1[1][0] = int(var1.row2element1)
            if  var1.row2element2 != None:
                mtx1[1][1] = int(var1.row2element2)
            if  var1.row2element3 != None:
                mtx1[1][2] = int(var1.row2element3)
            if  var1.row2element4 != None:
                mtx1[1][3] = int(var1.row2element4)
            if  var1.row2element5 != None:
                mtx1[1][4] = int(var1.row2element5)
            if  var1.row3element1 != None:
                mtx1[2][0] = int(var1.row3element1)
            if  var1.row3element2 != None:
                mtx1[2][1] = int(var1.row3element2)
            if  var1.row3element3 != None:
                mtx1[2][2] = int(var1.row3element3)
            if  var1.row3element4 != None:
                mtx1[2][3] = int(var1.row3element4)
            if  var1.row3element5 != None:
                mtx1[2][4] = int(var1.row3element5)
            if  var1.row4element1 != None:
                mtx1[3][0] = int(var1.row4element1)
            if  var1.row4element2 != None:
                mtx1[3][1] = int(var1.row4element2)
            if  var1.row4element3 != None:
                mtx1[3][2] = int(var1.row4element3)
            if  var1.row4element4 != None:
                mtx1[3][3] = int(var1.row4element4)
            if  var1.row4element5 != None:
                mtx1[3][4] = int(var1.row4element5)
            if  var1.row5element1 != None:
                mtx1[4][0] = int(var1.row5element1)
            if  var1.row5element2 != None:
                mtx1[4][1] = int(var1.row5element2)
            if  var1.row5element3 != None:
                mtx1[4][2] = int(var1.row5element3)
            if  var1.row5element4 != None:
                mtx1[4][3] = int(var1.row5element4)
            if  var1.row5element5 != None:
                mtx1[4][4] = int(var1.row5element5)

            if  var2.row1element1 != None:
                mtx2[0][0] = int(var2.row1element1)
            if  var2.row1element2 != None:
                mtx2[0][1] = int(var2.row1element2)
            if  var2.row1element3 != None:
                mtx2[0][2] = int(var2.row1element3)
            if  var2.row1element4 != None:
                mtx2[0][3] = int(var2.row1element4)
            if  var2.row1element5 != None:
                mtx2[0][4] = int(var2.row1element5)
            if  var2.row2element1 != None:
                mtx2[1][0] = int(var2.row2element1)
            if  var2.row2element2 != None:
                mtx2[1][1] = int(var2.row2element2)
            if  var2.row2element3 != None:
                mtx2[1][2] = int(var2.row2element3)
            if  var2.row2element4 != None:
                mtx2[1][3] = int(var2.row2element4)
            if  var2.row2element5 != None:
                mtx2[1][4] = int(var2.row2element5)
            if  var2.row3element1 != None:
                mtx2[2][0] = int(var2.row3element1)
            if  var2.row3element2 != None:
                mtx2[2][1] = int(var2.row3element2)
            if  var2.row3element3 != None:
                mtx2[2][2] = int(var2.row3element3)
            if  var2.row3element4 != None:
                mtx2[2][3] = int(var2.row3element4)
            if  var2.row3element5 != None:
                mtx2[2][4] = int(var2.row3element5)
            if  var2.row4element1 != None:
                mtx2[3][0] = int(var2.row4element1)
            if  var2.row4element2 != None:
                mtx2[3][1] = int(var2.row4element2)
            if  var2.row4element3 != None:
                mtx2[3][2] = int(var2.row4element3)
            if  var2.row4element4 != None:
                mtx2[3][3] = int(var2.row4element4)
            if  var2.row4element5 != None:
                mtx2[3][4] = int(var2.row4element5)
            if  var2.row5element1 != None:
                mtx2[4][0] = int(var2.row5element1)
            if  var2.row5element2 != None:
                mtx2[4][1] = int(var2.row5element2)
            if  var2.row5element3 != None:
                mtx2[4][2] = int(var2.row5element3)
            if  var2.row5element4 != None:
                mtx2[4][3] = int(var2.row5element4)
            if  var2.row5element5 != None:
                mtx2[4][4] = int(var2.row5element5)

           
            #logging.warning(mtx1)
            #logging.warning(mtx2)

            input_type = input_form.cleaned_data['input_type']

            if input_type == 'add':
                if(row1 == row2 and col1 == col2):
                    result = []
                    for i in range(len(mtx1)):
                        row = []
                        for j in range(len(mtx1[i])):
                            row.append(mtx1[i][j] + mtx2[i][j])
                        result.append(row)
                    logging.warning(result)
                    if(len(result) > 4):
                        request.session['output4'] = ', '.join(str(v) for v in result[4]) 
                    else:
                        request.session['output4'] = ''
                    if(len(result) > 3):
                        request.session['output3'] = ', '.join(str(v) for v in result[3])
                    else:
                        request.session['output3'] = ''
                    if(len(result) > 2):
                        request.session['output2'] = ', '.join(str(v) for v in result[2])
                    else:
                        request.session['output2'] = ''
                    if(len(result) > 1):
                        request.session['output1'] = ', '.join(str(v) for v in result[1])
                    else:
                        request.session['output1'] = ''
                    if(len(result) > 0):
                        request.session['output0'] = ', '.join(str(v) for v in result[0])
                    else:
                        request.session['output0'] = ''
                else:
                    request.session['output0'] = 'Invalid Result, dimensions must match.'
                    request.session['output1'] = ''
                    request.session['output2'] = ''
                    request.session['output3'] = ''
                    request.session['output4'] = ''

            if input_type == 'multiply':
                if(col1 == row2):
                    a = mtx1
                    b = mtx2
                    zip_b = zip(*b)
                    # uncomment next line if python 3 : 
                    zip_b = list(zip_b)
                    result = [[sum(ele_a*ele_b for ele_a, ele_b in zip(row_a, col_b)) 
                            for col_b in zip_b] for row_a in a]
                    logging.warning(result)
                    if(len(result) > 4):
                        request.session['output4'] = ', '.join(str(v) for v in result[4])
                    else:
                        request.session['output4'] = ''
                    if(len(result) > 3):
                        request.session['output3'] = ', '.join(str(v) for v in result[3])
                    else:
                        request.session['output3'] = ''
                    if(len(result) > 2):
                        request.session['output2'] = ', '.join(str(v) for v in result[2])
                    else:
                        request.session['output2'] = ''
                    if(len(result) > 1):
                        request.session['output1'] = ', '.join(str(v) for v in result[1])
                    else:
                        request.session['output1'] = ''
                    if(len(result) > 0):
                        request.session['output0'] = ', '.join(str(v) for v in result[0])
                    else:
                        request.session['output0'] = ''
                else:
                    request.session['output0'] = 'Invalid Operation, row # of B must equal col # of A'
                    request.session['output1'] = ''
                    request.session['output2'] = ''
                    request.session['output3'] = ''
                    request.session['output4'] = ''



            if input_type == 'rref':
                rref(mtx1)
                result = mtx1
                if(len(result) > 4):
                    request.session['output4'] = ', '.join(str(v) for v in result[4])
                else:
                    request.session['output4'] = ''
                if(len(result) > 3):
                    request.session['output3'] = ', '.join(str(v) for v in result[3])
                else:
                    request.session['output3'] = ''
                if(len(result) > 2):
                    request.session['output2'] = ', '.join(str(v) for v in result[2])
                else:
                    request.session['output2'] = ''
                if(len(result) > 1):
                    request.session['output1'] = ', '.join(str(v) for v in result[1])
                else:
                    request.session['output1'] = ''
                if(len(result) > 0):
                    request.session['output0'] = ', '.join(str(v) for v in result[0])
                else:
                    request.session['output0'] = ''

            if input_type == 'determinant':
                if(row1 == col1):
                    result = det(mtx1) 
                    #logging.warning(result)
                    request.session['output0'] = result
                    request.session['output1'] = ''
                    request.session['output2'] = ''
                    request.session['output3'] = ''
                    request.session['output4'] = ''
                else:
                    request.session['output0'] = 'Invalid Operation, not square matrix'
                    request.session['output1'] = ''
                    request.session['output2'] = ''
                    request.session['output3'] = ''
                    request.session['output4'] = ''


            if input_type == 'inverse':
                if(row1 == col1):
                    result = inverse(mtx1)
                    logging.warning(result)
                    if(len(result) > 4):
                        request.session['output4'] = ', '.join(str(v) for v in result[4])
                    else:
                        request.session['output4'] = ''
                    if(len(result) > 3):
                        request.session['output3'] = ', '.join(str(v) for v in result[3])
                    else:
                        request.session['output3'] = ''
                    if(len(result) > 2):
                        request.session['output2'] = ', '.join(str(v) for v in result[2])
                    else:
                        request.session['output2'] = ''
                    if(len(result) > 1):
                        request.session['output1'] = ', '.join(str(v) for v in result[1])
                    else:
                        request.session['output1'] = ''
                    if(len(result) > 0):
                        request.session['output0'] = ', '.join(str(v) for v in result[0])
                    else:
                        request.session['output0'] = ''


                else:
                    request.session['output0'] = 'Invalid Operation, not square matrix'
                    request.session['output1'] = ''
                    request.session['output2'] = ''
                    request.session['output3'] = ''
                    request.session['output4'] = ''

            request.session['input_type'] = input_type
            return redirect('/')
        else:
            return redirect('/')

class SizeFormView(FormView):
    form_class = SizeForm
    template_name = 'core/index.html'
    success_url = '/'
    
    def post(self, request, *args, **kwargs):
        size_form = self.form_class(request.POST)
        if size_form.is_valid():
            row_size = size_form.cleaned_data['row_size']
            col_size = size_form.cleaned_data['col_size']
            dataFlag = True
            size_form.save()
            request.session['col_size'] = col_size
            request.session['row_size'] = row_size
            request.session['dataFlag'] = dataFlag
            return redirect('/')
        else:
            return redirect('/')


class EntryNewFormView(FormView):
    form_class = EntryNewForm
    template_name = 'core/index.html'
    success_url = '/'


    def post(self, request, *args, **kwargs):
        logging.warning(request.session['new_list'])
        new_entry_form = EntryNewForm(self.request.POST, exclude_list=request.session['new_list'])
        if new_entry_form.is_valid():
            var = new_entry_form.save()
            if var:    
                var.user = request.user
                test = request.user.username
                logging.warning(var.user.username)
                var.row_length = int(request.session['row_size'])
                var.col_length = int(request.session['col_size'])
                try:
                    var.save();
                except Exception as e: 
                    logging.warning("Duplicate")
            return redirect('/')
        else:
            #new_entry_form.save()
            return redirect('/')


class RemoveFormView(FormView):
    form_class = RemoveForm
    template_name = 'core/index.html'
    success_url = '/'

    def post(self, request, *args, **kwargs):
        remove_form = self.form_class(request.POST)
        if remove_form.is_valid():
            var1 = remove_form.cleaned_data['input_1']
            Varia.objects.filter(id=var1.id).delete()
            return redirect('/')
        else:
            return redirect('/')

class ViewerFormView(FormView):
    form_class = ViewerForm
    template_name = 'core/index.html'
    success_url = '/'

    def post(self, request, *args, **kwargs):
        viewer_form = self.form_class(request.POST)
        if viewer_form.is_valid():
            var1 = viewer_form.cleaned_data['input_1']
            col1 = var1.row_length
            row1 = var1.col_length
            mtx1 = [ ([0] * col1) for row in range(row1) ]
            if  var1.row1element1 != None:
                mtx1[0][0] = int(var1.row1element1)
            if  var1.row1element2 != None:
                mtx1[0][1] = int(var1.row1element2)
            if  var1.row1element3 != None:
                mtx1[0][2] = int(var1.row1element3)
            if  var1.row1element4 != None:
                mtx1[0][3] = int(var1.row1element4)
            if  var1.row1element5 != None:
                mtx1[0][4] = int(var1.row1element5)
            if  var1.row2element1 != None:
                mtx1[1][0] = int(var1.row2element1)
            if  var1.row2element2 != None:
                mtx1[1][1] = int(var1.row2element2)
            if  var1.row2element3 != None:
                mtx1[1][2] = int(var1.row2element3)
            if  var1.row2element4 != None:
                mtx1[1][3] = int(var1.row2element4)
            if  var1.row2element5 != None:
                mtx1[1][4] = int(var1.row2element5)
            if  var1.row3element1 != None:
                mtx1[2][0] = int(var1.row3element1)
            if  var1.row3element2 != None:
                mtx1[2][1] = int(var1.row3element2)
            if  var1.row3element3 != None:
                mtx1[2][2] = int(var1.row3element3)
            if  var1.row3element4 != None:
                mtx1[2][3] = int(var1.row3element4)
            if  var1.row3element5 != None:
                mtx1[2][4] = int(var1.row3element5)
            if  var1.row4element1 != None:
                mtx1[3][0] = int(var1.row4element1)
            if  var1.row4element2 != None:
                mtx1[3][1] = int(var1.row4element2)
            if  var1.row4element3 != None:
                mtx1[3][2] = int(var1.row4element3)
            if  var1.row4element4 != None:
                mtx1[3][3] = int(var1.row4element4)
            if  var1.row4element5 != None:
                mtx1[3][4] = int(var1.row4element5)
            if  var1.row5element1 != None:
                mtx1[4][0] = int(var1.row5element1)
            if  var1.row5element2 != None:
                mtx1[4][1] = int(var1.row5element2)
            if  var1.row5element3 != None:
                mtx1[4][2] = int(var1.row5element3)
            if  var1.row5element4 != None:
                mtx1[4][3] = int(var1.row5element4)
            if  var1.row5element5 != None:
                mtx1[4][4] = int(var1.row5element5)

            result = mtx1

            if(len(result) > 4):
                request.session['array_row4'] = ', '.join(str(v) for v in result[4])
            else:
                request.session['array_row4'] = ''
            if(len(result) > 3):
                request.session['array_row3'] = ', '.join(str(v) for v in result[3])
            else:
                request.session['array_row3'] = ''
            if(len(result) > 2):
                request.session['array_row2'] = ', '.join(str(v) for v in result[2])
            else:
                request.session['array_row2'] = ''
            if(len(result) > 1):
                request.session['array_row1'] = ', '.join(str(v) for v in result[1])
            else:
                request.session['array_row1'] = ''
            if(len(result) > 0):
                request.session['array_row0'] = ', '.join(str(v) for v in result[0])
            else:
                request.session['array_row0'] = ''
            return redirect('/')
        else:
            return redirect('/')

def signup(request):
    if request.method == 'POST':
        form = UserCreationForm(request.POST)
        if form.is_valid():
            form.save()
            username = form.cleaned_data.get('username')
            raw_password = form.cleaned_data.get('password1')
            user = authenticate(username=username, password=raw_password)
            login(request, user)
            return redirect('/')
    else:
        form = UserCreationForm()
    return render(request, 'signup.html', {'form': form})

def rref( M):
    if not M: return
    lead = 0
    rowCount = len(M)
    logging.warning(M)
    columnCount = len(M[0])
    for r in range(rowCount):
        if lead >= columnCount:
            return
        i = r
        while M[i][lead] == 0:
            i += 1
            if i == rowCount:
                i = r
                lead += 1
                if columnCount == lead:
                    return
        M[i],M[r] = M[r],M[i]
        lv = M[r][lead]
        M[r] = [ mrx / float(lv) for mrx in M[r]]
        for i in range(rowCount):
            if i != r:
                lv = M[i][lead]
                M[i] = [ iv - lv*rv for rv,iv in zip(M[r],M[i])]
        lead += 1

def det(l):
    n=len(l)
    if (n>2):
        i=1
        t=0
        sum=0
        while t<=n-1:
            d={}
            t1=1
            while t1<=n-1:
                m=0
                d[t1]=[]
                while m<=n-1:
                    if (m==t):
                        u=0
                    else:
                        d[t1].append(l[t1][m])
                    m+=1
                t1+=1
            l1=[d[x] for x in d]
            sum=sum+i*(l[0][t])*(det(l1))
            i=i*(-1)
            t+=1
        return sum
    else:
        return (l[0][0]*l[1][1]-l[0][1]*l[1][0])

def transposeMatrix(m):
    return list(map(list,zip(*m)))

def getMatrixMinor(m,i,j):
    return [row[:j] + row[j+1:] for row in (m[:i]+m[i+1:])]

def inverse(m):
    determinant = det(m)
    #special case for 2x2 matrix:
    if len(m) == 2:
        return [[m[1][1]/determinant, -1*m[0][1]/determinant],
                [-1*m[1][0]/determinant, m[0][0]/determinant]]

    #find matrix of cofactors
    cofactors = []
    for r in range(len(m)):
        cofactorRow = []
        for c in range(len(m)):
            minor = getMatrixMinor(m,r,c)
            cofactorRow.append(((-1)**(r+c)) * det(minor))
        cofactors.append(cofactorRow)
    cofactors = transposeMatrix(cofactors)
    for r in range(len(cofactors)):
        for c in range(len(cofactors)):
            cofactors[r][c] = cofactors[r][c]/determinant
    return cofactors
