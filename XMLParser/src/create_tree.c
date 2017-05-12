#include	"XMLParser.h"
#include	<stdio.h>

int		str_is_num(const char *str)
{
  int		i = 0;

  while (str[i] != '\0')
    {
      if (str[i] < '0' && str[i] > '9')
	return (-1);
      i++;
    }
  return (0);
}

int		str_n_is_num(const char *str, int max)
{
  int		i = 0;

  while (str[i] != '\0' && i < max)
    {
      if (str[i] < '0' && str[i] > '9')
	return (-1);
      i++;
    }
  return (0);
}

int		is_a_token(const char *fragment, const char *sep)
{
  int		i = 0;

  while (fragment[i] != '\0')
    {
      if (strcis(sep, fragment[i]) == -1)
	return (-1);
      i++;
    }
  return (0);
}

void		state_token_fragment(const char *fragment, tree_parser *info)
{
  switch (fragment[0]) {
  case '=':
    (*info).current_state = ASSIGNEMENT;
    break ;
  case '\"':
    if ((*info).last_state == TYPETOKENB)
      (*info).current_state = TYPETOKENE;
    else
      (*info).current_state = TYPETOKENB;
    break ;
  case '<':
    (*info).current_state = DECLARATIONB;
    break ;
  case '>':
    (*info).current_state = DECLARATIONE;
    break ;
  case '/':
    (*info).current_state = DECLARATIONE;
    break ;
  default :
    break ;
  }
}

void		identify_token_type(const char *fragment, tree_parser *info)
{
  int		decimal_pos;

  if (fragment[0] == '\"')
    {
      (*info).value_type = STRING;
      (*info).current_state = VALUE;
      (*info).current_tree_type = ATTRIBUT;
      return ;
    }
  if (strcmp(fragment, "null") == 0)
    {
      (*info).value_type = NULLOBJ;
      (*info).current_state = VALUE;
      (*info).current_tree_type = ATTRIBUT;
      return ;
    }
  if (strcmp(fragment, "true") == 0 || strcmp(fragment, "false") == 0)
    {
      (*info).value_type = BOOL;
      (*info).current_state = VALUE;
      (*info).current_tree_type = ATTRIBUT;
      return ;
    }
  if ((decimal_pos = strcis(fragment, '.')) != -1 && str_n_is_num(fragment, decimal_pos) == 0 \
      && str_is_num(fragment + decimal_pos) == 0)
    {
      (*info).value_type = DECIMAL;
      (*info).current_state = VALUE;
      (*info).current_tree_type = ATTRIBUT;
      return ;
    }
  if (str_is_num(fragment) == 0)
    {
      (*info).value_type = INTEGER;
      (*info).current_state = VALUE;
      (*info).current_tree_type = ATTRIBUT;
      return ;
    }
  (*info).value_type = UNKNOW;
  return ;
}

void		add_segment(tree_parser *info, message **msg)
{
  int		is_a_group;

  is_a_group = ((*info).current_tree_type == SEGMENT) ? 0 : 1;
  newSegment(&((*msg)->segment), (*info).elem_name, lastSegmentID((*msg)->segment) + 1, \
	     is_a_group, (*info).is_in_list, (*info).is_in_list);
  if ((*info).elem_name != NULL)
    free((*info).elem_name);
  (*info).elem_name = NULL;
  (*info).last_tree_type = (*info).current_tree_type;
  (*info).current_tree_type = NOPE;
  if (is_a_group)
    (*info).is_in_list++;
}

void		add_chunk_to_tree(tree_parser *info, message **msg)
{
  switch ((*info).current_tree_type)
    {
    case CLOSEGROUP:
      closeGroupSegment(&((*msg)->segment));
      if ((*info).last_tree_type == TAB)
	(*info).is_in_tab = 0;
      else
	(*info).is_in_list--;	
      (*info).last_tree_type = (*info).current_tree_type;
      (*info).current_tree_type = NOPE;
      break;
    case SEGMENT:
      add_segment(info, msg);
      break;
    case LIST:
      add_segment(info, msg);
      break;
    case TAB:
      add_segment(info, msg);
      break;
    case ELEMENT:
      newElement(&((*msg)->segment->element), (*info).elem_name, lastElementID(((*msg)->segment->element)));
      if ((*info).elem_name != NULL)
	free((*info).elem_name);
      (*info).seg_name = NULL;
      (*info).last_tree_type = (*info).current_tree_type;
      (*info).current_tree_type = NOPE;
      break;
    case ATTRIBUT:
      if ((*info).content == NULL)
	return ;
      if (newElement(&((*msg)->segment->element), (*info).elem_name,	\
		     lastElementID(((*msg)->segment->element)) + 1) == 0)
	{
	  (*info).current_state = ERROR;
	  return ;
	}
      newAttribut(&((*msg)->segment->element->attribut), (*info).attr_name, \
		  lastAttributID(((*msg)->segment->element->attribut)) + 1, (*info).content, (*info).value_type);
      if ((*info).attr_name != NULL)
	free((*info).attr_name);
      (*info).attr_name = NULL;
      if ((*info).elem_name != NULL)
	free((*info).elem_name);
      (*info).elem_name = NULL;
      if ((*info).content != NULL)
	free((*info).content);
      (*info).content = NULL;
      (*info).value_type = UNKNOW;
      (*info).current_tree_type = NOPE;
      if ((*info).last_tree_type != TAB)
	(*info).last_tree_type = ATTRIBUT;
      break;
    default:
      break;
    }
}

tree_parser	init_tree_parser()
{
  tree_parser	info;

  info.seg_name = NULL;
  info.elem_name = NULL;
  info.attr_name = NULL;
  info.content = NULL;
  info.current_state = NONE;
  info.last_state = NONE;
  info.current_tree_type = NONE;
  info.last_tree_type = NONE;
  info.is_in_list = 0;
  info.is_in_tab = 0;
  return (info);
}

message		*create_tree(char **tokens)
{
  message	*ret;
  int		i;
  tree_parser	info;
  
  ret = NULL;
  info = init_tree_parser();
  newMessage(&ret, 1);
  i = 0;
  while (tokens[i] != NULL)
    {
      if (info.current_state == ERROR)
	{
	  dprintf(2, "SYNTAX ERROR\n");
	  deleteMessages(&ret);
	  return (NULL);
	}
      if (is_a_token(tokens[i], "<>/\"=\'") == 0)
	state_token_fragment(tokens[i], &info);
      else
	{
	  if (info.last_state == DECLARATIONB && info.elem_name != NULL)
	    
	  if (info.last_state == DECLARATIONB && info.elem_name == NULL)
	    info.elem_name = strdup(tokens[i]);
	  if (info.last_state == ASSIGNEMENT || info.last_state == TYPETOKENB)
	    {
	      identify_token_type(tokens[(info.last_state == TYPETOKENB && i > 0) ? i - 1 : i], &info);
	      info.content = strdup(tokens[i]);
	    }
	}
      if (info.current_tree_type != NOPE)
	add_chunk_to_tree(&info, &ret);
      i++;
      info.last_state = info.current_state;
    }
  return (ret);
}
