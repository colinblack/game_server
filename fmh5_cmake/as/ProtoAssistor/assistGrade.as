package com.sanguo.game.server.connectlogic.common.message.ProtoAssistor
{
	import laya.utils.Byte;
	public class assistGrade
	{
		public static const PROTO:String = "ProtoAssistor.assistGrade";
		public var package_root:*;
		public  var message:*;
		public var times:int;
		public var cash:int;
		public function assistGrade(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			times = undefined;
			cash = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.times = this.times;
			serializeObj.cash = this.cash;
			return serializeObj;
		}
		public function unserialize(msgObj:*):assistGrade
		{
			times = undefined;
			cash = undefined;
			this.times = msgObj.times;
			this.cash = msgObj.cash;
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):assistGrade
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}