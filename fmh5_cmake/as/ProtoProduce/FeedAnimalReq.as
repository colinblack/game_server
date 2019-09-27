package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class FeedAnimalReq
	{
		public static const PROTO:String = "ProtoProduce.FeedAnimalReq";
		public var package_root:*;
		public  var message:*;
		public var animalud:int;
		public var fodderud:int;
		public function FeedAnimalReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			animalud = undefined;
			fodderud = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.animalud = this.animalud;
			serializeObj.fodderud = this.fodderud;
			return serializeObj;
		}
		public function unserialize(msgObj:*):FeedAnimalReq
		{
			animalud = undefined;
			fodderud = undefined;
			this.animalud = msgObj.animalud;
			this.fodderud = msgObj.fodderud;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FeedAnimalReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}