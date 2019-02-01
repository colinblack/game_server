package com.sanguo.game.server.connectlogic.common.message.ProtoPush
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class PushMartialIncomeUpdate
	{
		public static const PROTO:String = "ProtoPush.PushMartialIncomeUpdate";
		public var package_root:*;
		public  var message:*;
		public function PushMartialIncomeUpdate(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			return serializeObj;
		}
		public function unserialize(msgObj:*):PushMartialIncomeUpdate
		{
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushMartialIncomeUpdate
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}