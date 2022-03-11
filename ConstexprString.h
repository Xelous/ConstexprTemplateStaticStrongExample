#pragma once

namespace xelous::ConstExpr
{
  template<std::size_t Length>
  struct TemplateString
  {
    // Constructor is constexpr and simply copies the payload text
    // into the member data setup
    constexpr TemplateString(const char(&pPayloadText)[Length + 1])
    {
      std::copy_n(pPayloadText, Length+1, mText);
    }
    
    auto operator<=>(const TemplateString&) const = default;
    
    // Default is just an empty buffer of the Length+1
    char mText[Length+1] = {};
  };
  
  // Make decaying the template Length possible
  template<std::size_t Length>
  TemplateString(const char(&str)[Length])->TemplateString<Length-1>;

} // End of namespace
