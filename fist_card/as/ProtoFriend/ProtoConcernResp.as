package com.sanguo.game.server.connectlogic.common.message.ProtoFriend
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoConcernResp
	{
		public static const PROTO:String = "ProtoFriend.ProtoConcernResp";
		public var package_root:*;
		public  var message:*;
		public var info:RecommendInfo;
		public function ProtoConcernResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			info = undefined;
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			if(this.info!= undefined)
			{
				serializeObj.info = this.info.serialize();
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoConcernResp
		{
			info = undefined;
			if(msgObj.hasOwnProperty("info"))
			{
				this.info = new RecommendInfo(package_root).unserialize(msgObj.info);
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoConcernResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}