package com.sanguo.game.server.connectlogic.common.message.ProtoBattle
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoRandomUserReq
	{
		public static const PROTO:String = "ProtoBattle.ProtoRandomUserReq";
		public var package_root:*;
		public  var message:*;
		public var common:BattleCommonCPP;
		public function ProtoRandomUserReq(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			common = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.common!= undefined)
			{
				serializeObj.common = this.common.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoRandomUserReq
		{
			common = undefined;
			if(msgObj.hasOwnProperty("common"))
			{
				this.common = new BattleCommonCPP(package_root).unserialize(msgObj.common);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoRandomUserReq
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}