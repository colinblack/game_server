package com.sanguo.game.server.connectlogic.common.message.User
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class OnhookOnlinePropReward
	{
		public static const PROTO:String = "User.OnhookOnlinePropReward";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public function OnhookOnlinePropReward(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.commons = this.commons.serialize();
			return serializeObj;
		}
		public function unserialize(msgObj:*):OnhookOnlinePropReward
		{
			commons = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):OnhookOnlinePropReward
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}