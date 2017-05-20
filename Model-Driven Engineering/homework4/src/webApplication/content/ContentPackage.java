/**
 */
package webApplication.content;

import org.eclipse.emf.ecore.EAttribute;
import org.eclipse.emf.ecore.EClass;
import org.eclipse.emf.ecore.EEnum;
import org.eclipse.emf.ecore.EPackage;
import org.eclipse.emf.ecore.EReference;

import webApplication.WebApplicationPackage;

/**
 * <!-- begin-user-doc -->
 * The <b>Package</b> for the model.
 * It contains accessors for the meta objects to represent
 * <ul>
 *   <li>each class,</li>
 *   <li>each feature of each class,</li>
 *   <li>each operation of each class,</li>
 *   <li>each enum,</li>
 *   <li>and each data type</li>
 * </ul>
 * <!-- end-user-doc -->
 * @see webApplication.content.ContentFactory
 * @model kind="package"
 * @generated
 */
public interface ContentPackage extends EPackage {
	/**
	 * The package name.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	String eNAME = "content";

	/**
	 * The package namespace URI.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	String eNS_URI = "http://org.disim/WebApplication/content";

	/**
	 * The package namespace name.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	String eNS_PREFIX = "content";

	/**
	 * The singleton instance of the package.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 */
	ContentPackage eINSTANCE = webApplication.content.impl.ContentPackageImpl.init();

	/**
	 * The meta object id for the '{@link webApplication.content.impl.PageImpl <em>Page</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see webApplication.content.impl.PageImpl
	 * @see webApplication.content.impl.ContentPackageImpl#getPage()
	 * @generated
	 */
	int PAGE = 0;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PAGE__NAME = WebApplicationPackage.NAMED__NAME;

	/**
	 * The feature id for the '<em><b>Contents</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PAGE__CONTENTS = WebApplicationPackage.NAMED_FEATURE_COUNT + 0;

	/**
	 * The feature id for the '<em><b>Links</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PAGE__LINKS = WebApplicationPackage.NAMED_FEATURE_COUNT + 1;

	/**
	 * The feature id for the '<em><b>Forms</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PAGE__FORMS = WebApplicationPackage.NAMED_FEATURE_COUNT + 2;

	/**
	 * The number of structural features of the '<em>Page</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PAGE_FEATURE_COUNT = WebApplicationPackage.NAMED_FEATURE_COUNT + 3;

	/**
	 * The number of operations of the '<em>Page</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int PAGE_OPERATION_COUNT = WebApplicationPackage.NAMED_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link webApplication.content.impl.ContentImpl <em>Content</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see webApplication.content.impl.ContentImpl
	 * @see webApplication.content.impl.ContentPackageImpl#getContent()
	 * @generated
	 */
	int CONTENT = 1;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CONTENT__NAME = WebApplicationPackage.NAMED__NAME;

	/**
	 * The feature id for the '<em><b>Data Source</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CONTENT__DATA_SOURCE = WebApplicationPackage.NAMED_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Content</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CONTENT_FEATURE_COUNT = WebApplicationPackage.NAMED_FEATURE_COUNT + 1;

	/**
	 * The number of operations of the '<em>Content</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CONTENT_OPERATION_COUNT = WebApplicationPackage.NAMED_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link webApplication.content.impl.FormImpl <em>Form</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see webApplication.content.impl.FormImpl
	 * @see webApplication.content.impl.ContentPackageImpl#getForm()
	 * @generated
	 */
	int FORM = 2;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FORM__NAME = WebApplicationPackage.NAMED__NAME;

	/**
	 * The number of structural features of the '<em>Form</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FORM_FEATURE_COUNT = WebApplicationPackage.NAMED_FEATURE_COUNT + 0;

	/**
	 * The number of operations of the '<em>Form</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FORM_OPERATION_COUNT = WebApplicationPackage.NAMED_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link webApplication.content.impl.LinkImpl <em>Link</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see webApplication.content.impl.LinkImpl
	 * @see webApplication.content.impl.ContentPackageImpl#getLink()
	 * @generated
	 */
	int LINK = 3;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int LINK__NAME = WebApplicationPackage.NAMED__NAME;

	/**
	 * The feature id for the '<em><b>From</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int LINK__FROM = WebApplicationPackage.NAMED_FEATURE_COUNT + 0;

	/**
	 * The feature id for the '<em><b>To</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int LINK__TO = WebApplicationPackage.NAMED_FEATURE_COUNT + 1;

	/**
	 * The number of structural features of the '<em>Link</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int LINK_FEATURE_COUNT = WebApplicationPackage.NAMED_FEATURE_COUNT + 2;

	/**
	 * The number of operations of the '<em>Link</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int LINK_OPERATION_COUNT = WebApplicationPackage.NAMED_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link webApplication.content.impl.MenuImpl <em>Menu</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see webApplication.content.impl.MenuImpl
	 * @see webApplication.content.impl.ContentPackageImpl#getMenu()
	 * @generated
	 */
	int MENU = 4;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MENU__NAME = CONTENT__NAME;

	/**
	 * The feature id for the '<em><b>Data Source</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MENU__DATA_SOURCE = CONTENT__DATA_SOURCE;

	/**
	 * The feature id for the '<em><b>Item Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MENU__ITEM_NAME = CONTENT_FEATURE_COUNT + 0;

	/**
	 * The feature id for the '<em><b>Url</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MENU__URL = CONTENT_FEATURE_COUNT + 1;

	/**
	 * The feature id for the '<em><b>Order</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MENU__ORDER = CONTENT_FEATURE_COUNT + 2;

	/**
	 * The number of structural features of the '<em>Menu</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MENU_FEATURE_COUNT = CONTENT_FEATURE_COUNT + 3;

	/**
	 * The number of operations of the '<em>Menu</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MENU_OPERATION_COUNT = CONTENT_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link webApplication.content.impl.SingleContentImpl <em>Single Content</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see webApplication.content.impl.SingleContentImpl
	 * @see webApplication.content.impl.ContentPackageImpl#getSingleContent()
	 * @generated
	 */
	int SINGLE_CONTENT = 5;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int SINGLE_CONTENT__NAME = CONTENT__NAME;

	/**
	 * The feature id for the '<em><b>Data Source</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int SINGLE_CONTENT__DATA_SOURCE = CONTENT__DATA_SOURCE;

	/**
	 * The number of structural features of the '<em>Single Content</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int SINGLE_CONTENT_FEATURE_COUNT = CONTENT_FEATURE_COUNT + 0;

	/**
	 * The number of operations of the '<em>Single Content</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int SINGLE_CONTENT_OPERATION_COUNT = CONTENT_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link webApplication.content.impl.MultipleContentImpl <em>Multiple Content</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see webApplication.content.impl.MultipleContentImpl
	 * @see webApplication.content.impl.ContentPackageImpl#getMultipleContent()
	 * @generated
	 */
	int MULTIPLE_CONTENT = 6;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MULTIPLE_CONTENT__NAME = CONTENT__NAME;

	/**
	 * The feature id for the '<em><b>Data Source</b></em>' reference.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MULTIPLE_CONTENT__DATA_SOURCE = CONTENT__DATA_SOURCE;

	/**
	 * The feature id for the '<em><b>Paginated</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MULTIPLE_CONTENT__PAGINATED = CONTENT_FEATURE_COUNT + 0;

	/**
	 * The feature id for the '<em><b>Size</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MULTIPLE_CONTENT__SIZE = CONTENT_FEATURE_COUNT + 1;

	/**
	 * The number of structural features of the '<em>Multiple Content</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MULTIPLE_CONTENT_FEATURE_COUNT = CONTENT_FEATURE_COUNT + 2;

	/**
	 * The number of operations of the '<em>Multiple Content</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int MULTIPLE_CONTENT_OPERATION_COUNT = CONTENT_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link webApplication.content.impl.CRUDFormImpl <em>CRUD Form</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see webApplication.content.impl.CRUDFormImpl
	 * @see webApplication.content.impl.ContentPackageImpl#getCRUDForm()
	 * @generated
	 */
	int CRUD_FORM = 7;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CRUD_FORM__NAME = FORM__NAME;

	/**
	 * The feature id for the '<em><b>Fields</b></em>' containment reference list.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CRUD_FORM__FIELDS = FORM_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>CRUD Form</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CRUD_FORM_FEATURE_COUNT = FORM_FEATURE_COUNT + 1;

	/**
	 * The number of operations of the '<em>CRUD Form</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int CRUD_FORM_OPERATION_COUNT = FORM_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link webApplication.content.impl.FieldImpl <em>Field</em>}' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see webApplication.content.impl.FieldImpl
	 * @see webApplication.content.impl.ContentPackageImpl#getField()
	 * @generated
	 */
	int FIELD = 8;

	/**
	 * The feature id for the '<em><b>Name</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FIELD__NAME = WebApplicationPackage.NAMED__NAME;

	/**
	 * The feature id for the '<em><b>Type</b></em>' attribute.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FIELD__TYPE = WebApplicationPackage.NAMED_FEATURE_COUNT + 0;

	/**
	 * The number of structural features of the '<em>Field</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FIELD_FEATURE_COUNT = WebApplicationPackage.NAMED_FEATURE_COUNT + 1;

	/**
	 * The number of operations of the '<em>Field</em>' class.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @generated
	 * @ordered
	 */
	int FIELD_OPERATION_COUNT = WebApplicationPackage.NAMED_OPERATION_COUNT + 0;

	/**
	 * The meta object id for the '{@link webApplication.content.FieldType <em>Field Type</em>}' enum.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @see webApplication.content.FieldType
	 * @see webApplication.content.impl.ContentPackageImpl#getFieldType()
	 * @generated
	 */
	int FIELD_TYPE = 9;


	/**
	 * Returns the meta object for class '{@link webApplication.content.Page <em>Page</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Page</em>'.
	 * @see webApplication.content.Page
	 * @generated
	 */
	EClass getPage();

	/**
	 * Returns the meta object for the containment reference list '{@link webApplication.content.Page#getContents <em>Contents</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Contents</em>'.
	 * @see webApplication.content.Page#getContents()
	 * @see #getPage()
	 * @generated
	 */
	EReference getPage_Contents();

	/**
	 * Returns the meta object for the containment reference list '{@link webApplication.content.Page#getLinks <em>Links</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Links</em>'.
	 * @see webApplication.content.Page#getLinks()
	 * @see #getPage()
	 * @generated
	 */
	EReference getPage_Links();

	/**
	 * Returns the meta object for the containment reference list '{@link webApplication.content.Page#getForms <em>Forms</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Forms</em>'.
	 * @see webApplication.content.Page#getForms()
	 * @see #getPage()
	 * @generated
	 */
	EReference getPage_Forms();

	/**
	 * Returns the meta object for class '{@link webApplication.content.Content <em>Content</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Content</em>'.
	 * @see webApplication.content.Content
	 * @generated
	 */
	EClass getContent();

	/**
	 * Returns the meta object for the reference '{@link webApplication.content.Content#getDataSource <em>Data Source</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>Data Source</em>'.
	 * @see webApplication.content.Content#getDataSource()
	 * @see #getContent()
	 * @generated
	 */
	EReference getContent_DataSource();

	/**
	 * Returns the meta object for class '{@link webApplication.content.Form <em>Form</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Form</em>'.
	 * @see webApplication.content.Form
	 * @generated
	 */
	EClass getForm();

	/**
	 * Returns the meta object for class '{@link webApplication.content.Link <em>Link</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Link</em>'.
	 * @see webApplication.content.Link
	 * @generated
	 */
	EClass getLink();

	/**
	 * Returns the meta object for the reference '{@link webApplication.content.Link#getFrom <em>From</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>From</em>'.
	 * @see webApplication.content.Link#getFrom()
	 * @see #getLink()
	 * @generated
	 */
	EReference getLink_From();

	/**
	 * Returns the meta object for the reference '{@link webApplication.content.Link#getTo <em>To</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the reference '<em>To</em>'.
	 * @see webApplication.content.Link#getTo()
	 * @see #getLink()
	 * @generated
	 */
	EReference getLink_To();

	/**
	 * Returns the meta object for class '{@link webApplication.content.Menu <em>Menu</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Menu</em>'.
	 * @see webApplication.content.Menu
	 * @generated
	 */
	EClass getMenu();

	/**
	 * Returns the meta object for the attribute '{@link webApplication.content.Menu#getItemName <em>Item Name</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Item Name</em>'.
	 * @see webApplication.content.Menu#getItemName()
	 * @see #getMenu()
	 * @generated
	 */
	EAttribute getMenu_ItemName();

	/**
	 * Returns the meta object for the attribute '{@link webApplication.content.Menu#getUrl <em>Url</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Url</em>'.
	 * @see webApplication.content.Menu#getUrl()
	 * @see #getMenu()
	 * @generated
	 */
	EAttribute getMenu_Url();

	/**
	 * Returns the meta object for the attribute '{@link webApplication.content.Menu#getOrder <em>Order</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Order</em>'.
	 * @see webApplication.content.Menu#getOrder()
	 * @see #getMenu()
	 * @generated
	 */
	EAttribute getMenu_Order();

	/**
	 * Returns the meta object for class '{@link webApplication.content.SingleContent <em>Single Content</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Single Content</em>'.
	 * @see webApplication.content.SingleContent
	 * @generated
	 */
	EClass getSingleContent();

	/**
	 * Returns the meta object for class '{@link webApplication.content.MultipleContent <em>Multiple Content</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Multiple Content</em>'.
	 * @see webApplication.content.MultipleContent
	 * @generated
	 */
	EClass getMultipleContent();

	/**
	 * Returns the meta object for the attribute '{@link webApplication.content.MultipleContent#isPaginated <em>Paginated</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Paginated</em>'.
	 * @see webApplication.content.MultipleContent#isPaginated()
	 * @see #getMultipleContent()
	 * @generated
	 */
	EAttribute getMultipleContent_Paginated();

	/**
	 * Returns the meta object for the attribute '{@link webApplication.content.MultipleContent#getSize <em>Size</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Size</em>'.
	 * @see webApplication.content.MultipleContent#getSize()
	 * @see #getMultipleContent()
	 * @generated
	 */
	EAttribute getMultipleContent_Size();

	/**
	 * Returns the meta object for class '{@link webApplication.content.CRUDForm <em>CRUD Form</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>CRUD Form</em>'.
	 * @see webApplication.content.CRUDForm
	 * @generated
	 */
	EClass getCRUDForm();

	/**
	 * Returns the meta object for the containment reference list '{@link webApplication.content.CRUDForm#getFields <em>Fields</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the containment reference list '<em>Fields</em>'.
	 * @see webApplication.content.CRUDForm#getFields()
	 * @see #getCRUDForm()
	 * @generated
	 */
	EReference getCRUDForm_Fields();

	/**
	 * Returns the meta object for class '{@link webApplication.content.Field <em>Field</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for class '<em>Field</em>'.
	 * @see webApplication.content.Field
	 * @generated
	 */
	EClass getField();

	/**
	 * Returns the meta object for the attribute '{@link webApplication.content.Field#getType <em>Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for the attribute '<em>Type</em>'.
	 * @see webApplication.content.Field#getType()
	 * @see #getField()
	 * @generated
	 */
	EAttribute getField_Type();

	/**
	 * Returns the meta object for enum '{@link webApplication.content.FieldType <em>Field Type</em>}'.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the meta object for enum '<em>Field Type</em>'.
	 * @see webApplication.content.FieldType
	 * @generated
	 */
	EEnum getFieldType();

	/**
	 * Returns the factory that creates the instances of the model.
	 * <!-- begin-user-doc -->
	 * <!-- end-user-doc -->
	 * @return the factory that creates the instances of the model.
	 * @generated
	 */
	ContentFactory getContentFactory();

	/**
	 * <!-- begin-user-doc -->
	 * Defines literals for the meta objects that represent
	 * <ul>
	 *   <li>each class,</li>
	 *   <li>each feature of each class,</li>
	 *   <li>each operation of each class,</li>
	 *   <li>each enum,</li>
	 *   <li>and each data type</li>
	 * </ul>
	 * <!-- end-user-doc -->
	 * @generated
	 */
	interface Literals {
		/**
		 * The meta object literal for the '{@link webApplication.content.impl.PageImpl <em>Page</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see webApplication.content.impl.PageImpl
		 * @see webApplication.content.impl.ContentPackageImpl#getPage()
		 * @generated
		 */
		EClass PAGE = eINSTANCE.getPage();

		/**
		 * The meta object literal for the '<em><b>Contents</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference PAGE__CONTENTS = eINSTANCE.getPage_Contents();

		/**
		 * The meta object literal for the '<em><b>Links</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference PAGE__LINKS = eINSTANCE.getPage_Links();

		/**
		 * The meta object literal for the '<em><b>Forms</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference PAGE__FORMS = eINSTANCE.getPage_Forms();

		/**
		 * The meta object literal for the '{@link webApplication.content.impl.ContentImpl <em>Content</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see webApplication.content.impl.ContentImpl
		 * @see webApplication.content.impl.ContentPackageImpl#getContent()
		 * @generated
		 */
		EClass CONTENT = eINSTANCE.getContent();

		/**
		 * The meta object literal for the '<em><b>Data Source</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference CONTENT__DATA_SOURCE = eINSTANCE.getContent_DataSource();

		/**
		 * The meta object literal for the '{@link webApplication.content.impl.FormImpl <em>Form</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see webApplication.content.impl.FormImpl
		 * @see webApplication.content.impl.ContentPackageImpl#getForm()
		 * @generated
		 */
		EClass FORM = eINSTANCE.getForm();

		/**
		 * The meta object literal for the '{@link webApplication.content.impl.LinkImpl <em>Link</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see webApplication.content.impl.LinkImpl
		 * @see webApplication.content.impl.ContentPackageImpl#getLink()
		 * @generated
		 */
		EClass LINK = eINSTANCE.getLink();

		/**
		 * The meta object literal for the '<em><b>From</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference LINK__FROM = eINSTANCE.getLink_From();

		/**
		 * The meta object literal for the '<em><b>To</b></em>' reference feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference LINK__TO = eINSTANCE.getLink_To();

		/**
		 * The meta object literal for the '{@link webApplication.content.impl.MenuImpl <em>Menu</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see webApplication.content.impl.MenuImpl
		 * @see webApplication.content.impl.ContentPackageImpl#getMenu()
		 * @generated
		 */
		EClass MENU = eINSTANCE.getMenu();

		/**
		 * The meta object literal for the '<em><b>Item Name</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute MENU__ITEM_NAME = eINSTANCE.getMenu_ItemName();

		/**
		 * The meta object literal for the '<em><b>Url</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute MENU__URL = eINSTANCE.getMenu_Url();

		/**
		 * The meta object literal for the '<em><b>Order</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute MENU__ORDER = eINSTANCE.getMenu_Order();

		/**
		 * The meta object literal for the '{@link webApplication.content.impl.SingleContentImpl <em>Single Content</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see webApplication.content.impl.SingleContentImpl
		 * @see webApplication.content.impl.ContentPackageImpl#getSingleContent()
		 * @generated
		 */
		EClass SINGLE_CONTENT = eINSTANCE.getSingleContent();

		/**
		 * The meta object literal for the '{@link webApplication.content.impl.MultipleContentImpl <em>Multiple Content</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see webApplication.content.impl.MultipleContentImpl
		 * @see webApplication.content.impl.ContentPackageImpl#getMultipleContent()
		 * @generated
		 */
		EClass MULTIPLE_CONTENT = eINSTANCE.getMultipleContent();

		/**
		 * The meta object literal for the '<em><b>Paginated</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute MULTIPLE_CONTENT__PAGINATED = eINSTANCE.getMultipleContent_Paginated();

		/**
		 * The meta object literal for the '<em><b>Size</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute MULTIPLE_CONTENT__SIZE = eINSTANCE.getMultipleContent_Size();

		/**
		 * The meta object literal for the '{@link webApplication.content.impl.CRUDFormImpl <em>CRUD Form</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see webApplication.content.impl.CRUDFormImpl
		 * @see webApplication.content.impl.ContentPackageImpl#getCRUDForm()
		 * @generated
		 */
		EClass CRUD_FORM = eINSTANCE.getCRUDForm();

		/**
		 * The meta object literal for the '<em><b>Fields</b></em>' containment reference list feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EReference CRUD_FORM__FIELDS = eINSTANCE.getCRUDForm_Fields();

		/**
		 * The meta object literal for the '{@link webApplication.content.impl.FieldImpl <em>Field</em>}' class.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see webApplication.content.impl.FieldImpl
		 * @see webApplication.content.impl.ContentPackageImpl#getField()
		 * @generated
		 */
		EClass FIELD = eINSTANCE.getField();

		/**
		 * The meta object literal for the '<em><b>Type</b></em>' attribute feature.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @generated
		 */
		EAttribute FIELD__TYPE = eINSTANCE.getField_Type();

		/**
		 * The meta object literal for the '{@link webApplication.content.FieldType <em>Field Type</em>}' enum.
		 * <!-- begin-user-doc -->
		 * <!-- end-user-doc -->
		 * @see webApplication.content.FieldType
		 * @see webApplication.content.impl.ContentPackageImpl#getFieldType()
		 * @generated
		 */
		EEnum FIELD_TYPE = eINSTANCE.getFieldType();

	}

} //ContentPackage
