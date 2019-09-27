package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class FeedAnimalResp
	{
		public static const PROTO:String = "ProtoProduce.FeedAnimalResp";
		public var package_root:*;
		public  var message:*;
		public var animal:AnimalCPP;
		public var commons:CommonItemsCPP;
		public function FeedAnimalResp(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			animal = undefined;
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.animal = this.animal.serialize();
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):FeedAnimalResp
		{
			animal = undefined;
			commons = undefined;
			this.animal = new AnimalCPP(package_root).unserialize(msgObj.animal);
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):FeedAnimalResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}