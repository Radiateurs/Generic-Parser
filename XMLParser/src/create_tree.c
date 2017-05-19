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

void		state_token_fragment(const char *fragment, tree_parser *info, message *msg)
{
  msg = msg;
  
  switch (fragment[0]) {
  case '=':
    (*info).current_state = ASSIGNEMENT;
    break ;
  case '\"':
    if ((*info).last_state == VALUE)
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
    (*info).current_state = LISTE;
    (*info).current_tree_type = CLOSEGROUP;
    break ;
  default :
    break ;
  }
}

void		identify_token_type(const char *fragment, tree_parser *info)
{
  if (fragment[0] == '\"')
    {
      (*info).value_type = STRING;
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
  int		seg_type;

  is_a_group = ((*info).current_tree_type == SEGMENT) ? 0 : 1;
  seg_type = ((*info).current_tree_type == SEGMENT) ? SSEG : ((*info).current_tree_type == LIST) ? SLIST : STAB;
  newSegment(&((*msg)->segment), (*info).seg_name, getNextID((*msg)->segment),	\
	     is_a_group, 1, (*info).is_in_list + (*info).is_in_tab, \
	     seg_type);
  if ((*info).seg_name != NULL)
    free((*info).seg_name);
  (*info).seg_name = NULL;
  (*info).last_tree_type = (*info).current_tree_type;
  (*info).current_tree_type = NOPE;
  if (is_a_group)
    (*info).is_in_list++;
}

void		add_chunk_to_tree(tree_parser *info, message **msg)
{
  char		*tmp;

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
      if ((*info).elem_name[0] != (*info).textChar)
	{
	  (*info).seg_name = malloc(sizeof(char) * 2);
	  (*info).seg_name[0] = (*info).attrChar;
	  (*info).seg_name[1] = '\0';
	  tmp = mconcat((*info).seg_name, (*info).elem_name);
	  free((*info).elem_name);
	  free((*info).seg_name);
	  (*info).elem_name = strdup(tmp);
	  free(tmp);
	  (*info).seg_name = NULL;
	}
      newElement(&((*msg)->segment->element), (*info).elem_name, getNextID((*msg)->segment));
      if ((*info).elem_name != NULL)
	free((*info).elem_name);
      (*info).elem_name = NULL;
      (*info).last_tree_type = (*info).current_tree_type;
      (*info).current_tree_type = NOPE;
      break;
    case ATTRIBUT:
      puts((*msg)->segment->name);
      if ((*info).content == NULL)
	return ;
      if (((*msg)->segment != NULL && (*msg)->segment->element == NULL) || (*info).elem_name != NULL)
	if (newElement(&((*msg)->segment->element), (*info).elem_name,	\
		       getNextID((*msg)->segment)) != 1)
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
  info.textChar = '#';
  info.attrChar = '@';
  return (info);
}

void		getTextData(int *i, char **tokens, tree_parser *info)
{ 
  char		*tmp;

  while (tokens[*i] != NULL && tokens[*i][0] != '<')
    {
      if (is_a_token(tokens[*i], ">/\"=\'") == 0)
	{
	  tmp = mconcat((*info).content, tokens[*i]);
	  free((*info).content);
	  (*info).content = strdup(tmp);
	  free(tmp);
	}
      else
	{
	  tmp = mconcat((*info).content, " ");
	  free((*info).content);
	  (*info).content = strdup(tmp);
	  free(tmp);
	  tmp = mconcat((*info).content, tokens[*i]);
	  free((*info).content);
	  (*info).content = strdup(tmp);
	  free(tmp);
	}
      (*i)++;
    }
  (*i)--;
  (*info).elem_name = malloc(sizeof(char) * 2);
  (*info).elem_name[0] = (*info).textChar;
  (*info).elem_name[1] = '\0';
  tmp = mconcat((*info).elem_name, "TEXT");
  free((*info).elem_name);
  (*info).elem_name = strdup(tmp);
  free(tmp);
  (*info).value_type = STRING;
  (*info).current_tree_type = ATTRIBUT;
}

void		findAndModifyListInTab(segment **seg)
{
  segment	*tmp;

  if (countSegment((*seg)->child) > 1)
    {
      while ((*seg)->child != NULL && (*seg)->child->prev != NULL)
	(*seg)->child = (*seg)->child->prev;
      tmp = (*seg)->child;
      (*seg)->child = (*seg)->child->next;
      while ((*seg)->child != NULL && (*seg)->child->next != NULL)
	{
	  if (strcmp((*seg)->child->name, tmp->name) == 0)
	    {
	      addParent(seg, tmp->name);
	      while ((*seg)->child != NULL && (*seg)->child->prev != NULL)
		(*seg)->child = (*seg)->child->prev;
	      tmp = (*seg)->child;
	    }
	  (*seg)->child = (*seg)->child->next;
	}
    }
}

message		*xmlParseTab(message *msg)
{
  segment	*tmp;

  tmp = msg->segment;
  while (tmp != NULL && tmp->child != NULL)
    {
      while (tmp->prev != NULL)
	tmp = tmp->prev;
      while (tmp->next != NULL)
	{
	  findAndModifyListInTab(&tmp->child);
	  tmp = tmp->next;
	}
    }
  return (msg);
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
	state_token_fragment(tokens[i], &info, ret);
      if (is_a_token(tokens[i], "<>/\"=\'") != 0 ||			\
	  (info.last_state == DECLARATIONB && info.current_state != LISTE) || \
	  info.last_state == TYPETOKENB || info.current_state == ESNAME || info.current_state == VALUE)
	{
	  if (info.last_state == DECLARATIONE)
	    getTextData(&i, tokens, &info);
	  if (info.last_state == ESNAME || info.last_state == TYPETOKENE)
	    {
	      info.current_state = ESNAME;
	      info.current_tree_type = ELEMENT;
	      info.elem_name = strdup(tokens[i]);
	    }
	  if (info.last_state == DECLARATIONB && info.seg_name == NULL)
	    {
	      info.current_state = ESNAME;
	      info.current_tree_type = LIST;
	      info.seg_name = strdup(tokens[i]);
	    }
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
  if (info.content != NULL)
    free(info.content);
  if (info.seg_name != NULL)
    free(info.seg_name);
  if (info.elem_name != NULL)
    free(info.elem_name);
  return (xmlParseTab(ret));
}
