package com.sanguo.game.server.connectlogic.common.message.ProtoMartialClub
{
	import com.sanguo.game.server.ServerManager;
	import laya.utils.Byte;
	public class ProtoCSGetPartTimeClubResp
	{
		public static const PROTO:String = "ProtoMartialClub.ProtoCSGetPartTimeClubResp";
		public var package_root:*;
		public  var message:*;
		public var info:Vector.<SingleMartialClub>;
		public function ProtoCSGetPartTimeClubResp(root:*)
		{
			package_root = root;
			message = ServerManager.getProtoMsg(PROTO);
			info = new Vector.<SingleMartialClub>();
		}
		public function serialize():*
		{
			var serializeObj:Object = {};
			serializeObj.info = [];
			for(var i:int = 0;i < this.info.length;i++)
			{
				serializeObj.info.push(this.info[i].serialize());
			}
			return serializeObj;
		}
		public function unserialize(msgObj:*):ProtoCSGetPartTimeClubResp
		{
			info = new Vector.<SingleMartialClub>();
			for(var i:int = 0;i < msgObj.info.length;i++)
			{
				this.info.push(new SingleMartialClub(package_root).unserialize(msgObj.info[i]));
			}
			return this;
		}
		public function encode():* 
		{
			return message.encode(serialize()).finish();
		}
		public function decode(buffer:*):ProtoCSGetPartTimeClubResp
		{
			var msg:* = message.decode(buffer);
			return unserialize(msg);
		}
	}
}