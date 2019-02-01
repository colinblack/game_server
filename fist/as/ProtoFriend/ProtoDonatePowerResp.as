package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoDonatePowerResp
	{
		public static const PROTO:String = "ProtoFriend.ProtoDonatePowerResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public function ProtoDonatePowerResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			commons = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.commons!= undefined)
			{
				serializeObj.commons = this.commons.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoDonatePowerResp
		{
			commons = undefined;
			if(msgObj.hasOwnProperty("commons"))
			{
				this.commons = new CommonItemsCPP(package_root).unserialize(msgObj.commons);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoDonatePowerResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}