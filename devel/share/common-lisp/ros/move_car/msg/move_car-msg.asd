
(cl:in-package :asdf)

(defsystem "move_car-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "car_parameter" :depends-on ("_package_car_parameter"))
    (:file "_package_car_parameter" :depends-on ("_package"))
  ))