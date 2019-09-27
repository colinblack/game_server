package com.sanguo.game.server.connectlogic.common.message.ProtoOrder
{
	import laya.utils.Byte;
	public class NeedCost
	{
		public static const PROTO:String = "ProtoOrder.NeedCost";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public var count:int;
		public function NeedCost(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
			count = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			serializeObj.count = this.count;
			return serializeObj;
		}
		public function unserialize(msgObj:*):NeedCost
		{
			id = undefined;
			count = undefined;
			this.id = msgObj.id;
			this.count = msgObj.count;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):NeedCost
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}