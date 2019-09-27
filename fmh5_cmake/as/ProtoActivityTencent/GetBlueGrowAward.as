package com.sanguo.game.server.connectlogic.common.message.ProtoActivityTencent
{
	import laya.utils.Byte;
	public class GetBlueGrowAward
	{
		public static const PROTO:String = "ProtoActivityTencent.GetBlueGrowAward";
		public var package_root:*;
		public  var message:*;
		public var id:int;
		public function GetBlueGrowAward(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			id = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.id = this.id;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetBlueGrowAward
		{
			id = undefined;
			this.id = msgObj.id;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetBlueGrowAward
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}