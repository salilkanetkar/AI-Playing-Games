from sklearn.preprocessing import OneHotEncoder
import pandas as pd
enc = OneHotEncoder()


def convert(x):
    try:
        return x.astype(int)
    except:
        return x

weapon = pd.read_csv("C:/Users/Salil Kanetkar/Downloads/org.eclipse.ldt.product-win32.win32.x86_64/workspace/CS188Test/src/dataforpistol/data10_wep.csv",header=None)
velocity = pd.read_csv("C:/Users/Salil Kanetkar/Downloads/org.eclipse.ldt.product-win32.win32.x86_64/workspace/CS188Test/src/dataforpistol/data10_vel.csv",header=None)

y=pd.DataFrame(enc.fit_transform(weapon).toarray())
y.apply(convert).to_csv(path_or_buf = "C:/Users/Salil Kanetkar/Downloads/org.eclipse.ldt.product-win32.win32.x86_64/workspace/CS188Test/src/dataforpistol/data10_wep_one.csv" ,header = False, index=False)

z=pd.DataFrame(enc.fit_transform(velocity).toarray())
z.apply(convert).to_csv(path_or_buf = "C:/Users/Salil Kanetkar/Downloads/org.eclipse.ldt.product-win32.win32.x86_64/workspace/CS188Test/src/dataforpistol/data10_vel_one.csv" ,header = False, index=False)
