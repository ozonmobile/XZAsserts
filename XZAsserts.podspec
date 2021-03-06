Pod::Spec.new do |s|
  s.name         = 'XZAsserts'
  s.version      = '1.0.2'
  s.license      =  { :type => 'MIT' }
  s.homepage     = 'https://github.com/xzeror/XZAsserts'
  s.authors      =  { 'xzeror' => 'xzeror@scryptmail.com' }
  s.summary      = 'Modified collection of assert macros, derived from FCYAssert project by Felipe Cypriano, that logs useful messages.'
  s.source       =  { :git => 'https://github.com/xzeror/XZAsserts.git', :tag => "v#{s.version}" }
  s.source_files = 'XZAsserts/*.{h,m}'
  s.requires_arc = true
end
