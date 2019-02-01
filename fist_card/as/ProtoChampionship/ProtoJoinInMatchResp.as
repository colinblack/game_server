package com.sanguo.game.server.connectlogic.common.message.ProtoChampionship
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoJoinInMatchResp
	{
		public static const PROTO:String = "ProtoChampionship.ProtoJoinInMatchResp";
		public var package_root:*;
		public  var message:*;
		public var commons:CommonItemsCPP;
		public function ProtoJoinInMatchResp(root:*)
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
		public function unserialize(msgObj:*):ProtoJoinInMatchResp
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
		public function decode(buffer:*):ProtoJoinInMatchResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}