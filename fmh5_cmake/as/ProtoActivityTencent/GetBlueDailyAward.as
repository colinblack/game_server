package com.sanguo.game.server.connectlogic.common.message.ProtoActivityTencent
{
	import laya.utils.Byte;
	public class GetBlueDailyAward
	{
		public static const PROTO:String = "ProtoActivityTencent.GetBlueDailyAward";
		public var package_root:*;
		public  var message:*;
		public var type:int;
		public function GetBlueDailyAward(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			type = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.type = this.type;
			return serializeObj;
		}
		public function unserialize(msgObj:*):GetBlueDailyAward
		{
			type = undefined;
			this.type = msgObj.type;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):GetBlueDailyAward
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}