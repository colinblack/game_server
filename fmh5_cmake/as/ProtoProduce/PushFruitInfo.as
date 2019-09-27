package com.sanguo.game.server.connectlogic.common.message.ProtoProduce
{
	import laya.utils.Byte;
	public class PushFruitInfo
	{
		public static const PROTO:String = "ProtoProduce.PushFruitInfo";
		public var package_root:*;
		public  var message:*;
		public var fruit:FruitCPP;
		public var uid:int;
		public function PushFruitInfo(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			fruit = undefined;
			uid = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.fruit = this.fruit.serialize();
			serializeObj.uid = this.uid;
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushFruitInfo
		{
			fruit = undefined;
			uid = undefined;
			this.fruit = new FruitCPP(package_root).unserialize(msgObj.fruit);
			this.uid = msgObj.uid;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushFruitInfo
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}