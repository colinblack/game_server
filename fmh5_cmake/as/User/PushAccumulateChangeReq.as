package com.sanguo.game.server.connectlogic.common.message.User
{
	import laya.utils.Byte;
	public class PushAccumulateChangeReq
	{
		public static const PROTO:String = "User.PushAccumulateChangeReq";
		public var package_root:*;
		public  var message:*;
		public var changeAcccharge:AccumulateCharge;
		public function PushAccumulateChangeReq(root:*)
		{
			package_root = root;
			message = root.lookup(PROTO);
			changeAcccharge = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.changeAcccharge = this.changeAcccharge.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushAccumulateChangeReq
		{
			changeAcccharge = undefined;
			this.changeAcccharge = new AccumulateCharge(package_root).unserialize(msgObj.changeAcccharge);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushAccumulateChangeReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}