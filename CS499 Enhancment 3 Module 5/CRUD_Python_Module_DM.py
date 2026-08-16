# Example Python Code to Insert a Document 

from pymongo import MongoClient 
from bson.objectid import ObjectId 

class AnimalShelter(object): 
    """ CRUD operations for Animal collection in MongoDB """ 

    def __init__(self, USER, PASS):
        # Initializing the MongoClient. This helps to access the MongoDB
        # databases and collections. This is hard-wired to use the
        # AAC_Animals database and the Animal_Records collection, on the
        # standalone demo mongod instance running on port 27018.
        #
        # That instance has no authentication configured, so pass empty
        # USER/PASS to connect without credentials; a non-empty USER will
        # still build a credentialed connection string for instances that
        # do enforce auth.
        #
        # Connection Variables
        #
        HOST = 'localhost'
        PORT = 27018
        DB = 'AAC_Animals'
        COL = 'Animal_Records'
        #
        # Initialize Connection
        #
        if USER:
            self.client = MongoClient('mongodb://%s:%s@%s:%d' % (USER,PASS,HOST,PORT))
        else:
            self.client = MongoClient('mongodb://%s:%d' % (HOST,PORT))
        self.database = self.client['%s' % (DB)]
        self.collection = self.database['%s' % (COL)]

    # Create a method to return the next available record number for use in the create method
            
    # method of creating records to implement the C in CRUD. 
    def create(self, data):
        try:
            if data is not None: # if data insert is not empty
                self.collection.insert_one(data)  # data should be dictionary
                return True # successful insert
            else:  
                return False # unsuccessful insert
        except Exception as e:
            print(f"Error creating record: {e}") # relevant error message
            return 0

    # method of reading records to implement the R in CRUD.
    # skip/limit enable server-side pagination - only the requested page's
    # documents are fetched, instead of the full matching result set. sort
    # gives skip/limit a stable ordering to page over - without one, MongoDB
    # does not guarantee page boundaries stay consistent between calls.
    def read(self, search, projection = None, skip = 0, limit = 0, sort = None):
        try:
            if projection:
                cursor = self.collection.find(search, projection)
            else:
                cursor = self.collection.find(search) # find query results in database
            if sort:
                cursor = cursor.sort(sort)
            if skip:
                cursor = cursor.skip(skip)
            if limit:
                cursor = cursor.limit(limit)
            result = list(cursor)
            for animal in result:
                print(animal, "\n") # list applicable results
        except Exception as e:
            print(f"Error finding record: {e}") # relevant error message
            result = []
        return result

    # returns the number of documents matching search without fetching them -
    # used to compute how many pages a filtered view has
    def count(self, search):
        try:
            return self.collection.count_documents(search)
        except Exception as e:
            print(f"Error counting records: {e}") # relevant error message
            return 0

    # method of updating records to implement the U in CRUD 
    def update(self, query, new_data):
        try:
            result = self.collection.update_many(query, {'$set' : new_data}) # update specifed query value using the set operator in Mongodb
            return f"Records updated: {result.modified_count}"
        except Exception as e:
            print(f"Error updating record: {e}") # relevant error message
            return 0
        
    # method of deleting records to implement the D in CRUD
    def delete(self, query):
        try:
            result = self.collection.delete_many(query) # remove all results that match the specified query
            return f"Records removed: {result.deleted_count}"
        except Exception as e:
            print(f"Error deleting record: {e}\n") # relevant error message
            return 0

    # runs an aggregation pipeline (e.g. $match + $group) on the server, so
    # summarizing/counting happens in MongoDB instead of after full documents
    # have already been pulled to the client
    def aggregate(self, pipeline):
        try:
            return list(self.collection.aggregate(pipeline)) # each stage runs server-side
        except Exception as e:
            print(f"Error running aggregation: {e}") # relevant error message
            return []
                