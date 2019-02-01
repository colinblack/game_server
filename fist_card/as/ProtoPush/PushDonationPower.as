package com.sanguo.game.server.connectlogic.common.message.ProtoPush
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class PushDonationPower
	{
		public static const PROTO:String = "ProtoPush.PushDonationPower";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public function PushDonationPower(root:*)
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
		public function unserialize(msgObj:*):PushDonationPower
		{
			commons = undefined;
			this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):PushDonationPower
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}